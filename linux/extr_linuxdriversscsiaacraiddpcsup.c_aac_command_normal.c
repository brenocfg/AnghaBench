#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u32 ;
struct hw_fib {scalar_t__ data; } ;
struct fib {int size; int /*<<< orphan*/  fiblink; struct aac_dev* dev; scalar_t__ data; struct hw_fib* hw_fib_va; int /*<<< orphan*/  type; } ;
struct aac_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  cmdready; int /*<<< orphan*/  cmdq; struct aac_dev* dev; } ;
struct aac_entry {int /*<<< orphan*/  addr; } ;
struct aac_dev {scalar_t__ aif_thread; struct hw_fib* aif_base_va; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  FSAFS_NTC_FIB_CONTEXT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HostNormCmdQueue ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ST_OK ; 
 int /*<<< orphan*/  aac_consumer_free (struct aac_dev*,struct aac_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ aac_consumer_get (struct aac_dev*,struct aac_queue*,struct aac_entry**) ; 
 int /*<<< orphan*/  aac_fib_adapter_complete (struct fib*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct fib* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fib*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

unsigned int aac_command_normal(struct aac_queue *q)
{
	struct aac_dev * dev = q->dev;
	struct aac_entry *entry;
	unsigned long flags;

	spin_lock_irqsave(q->lock, flags);

	/*
	 *	Keep pulling response QEs off the response queue and waking
	 *	up the waiters until there are no more QEs. We then return
	 *	back to the system.
	 */
	while(aac_consumer_get(dev, q, &entry))
	{
		struct fib fibctx;
		struct hw_fib * hw_fib;
		u32 index;
		struct fib *fib = &fibctx;
		
		index = le32_to_cpu(entry->addr) / sizeof(struct hw_fib);
		hw_fib = &dev->aif_base_va[index];
		
		/*
		 *	Allocate a FIB at all costs. For non queued stuff
		 *	we can just use the stack so we are happy. We need
		 *	a fib object in order to manage the linked lists
		 */
		if (dev->aif_thread)
			if((fib = kmalloc(sizeof(struct fib), GFP_ATOMIC)) == NULL)
				fib = &fibctx;
		
		memset(fib, 0, sizeof(struct fib));
		INIT_LIST_HEAD(&fib->fiblink);
		fib->type = FSAFS_NTC_FIB_CONTEXT;
		fib->size = sizeof(struct fib);
		fib->hw_fib_va = hw_fib;
		fib->data = hw_fib->data;
		fib->dev = dev;
		
				
		if (dev->aif_thread && fib != &fibctx) {
		        list_add_tail(&fib->fiblink, &q->cmdq);
	 	        aac_consumer_free(dev, q, HostNormCmdQueue);
		        wake_up_interruptible(&q->cmdready);
		} else {
	 	        aac_consumer_free(dev, q, HostNormCmdQueue);
			spin_unlock_irqrestore(q->lock, flags);
			/*
			 *	Set the status of this FIB
			 */
			*(__le32 *)hw_fib->data = cpu_to_le32(ST_OK);
			aac_fib_adapter_complete(fib, sizeof(u32));
			spin_lock_irqsave(q->lock, flags);
		}		
	}
	spin_unlock_irqrestore(q->lock, flags);
	return 0;
}