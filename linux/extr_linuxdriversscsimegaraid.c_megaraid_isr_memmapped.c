#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_13__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  quiescent; TYPE_2__* mbox; int /*<<< orphan*/  pend_cmds; } ;
typedef  TYPE_3__ adapter_t ;
struct TYPE_11__ {int numstatus; int status; scalar_t__ completed; } ;
struct TYPE_12__ {TYPE_1__ m_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int MAX_FIRMWARE_STATUS ; 
 int RDINDOOR (TYPE_3__*) ; 
 int RDOUTDOOR (TYPE_3__*) ; 
 int /*<<< orphan*/  WRINDOOR (TYPE_3__*,int) ; 
 int /*<<< orphan*/  WROUTDOOR (TYPE_3__*,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mega_cmd_done (TYPE_3__*,int*,int,int) ; 
 int /*<<< orphan*/  mega_rundoneq (TYPE_3__*) ; 
 int /*<<< orphan*/  mega_runpendq (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t
megaraid_isr_memmapped(int irq, void *devp)
{
	adapter_t	*adapter = devp;
	unsigned long	flags;
	u8	status;
	u32	dword = 0;
	u8	nstatus;
	u8	completed[MAX_FIRMWARE_STATUS];
	int	handled = 0;


	/*
	 * loop till F/W has more commands for us to complete.
	 */
	spin_lock_irqsave(&adapter->lock, flags);

	do {
		/* Check if a valid interrupt is pending */
		dword = RDOUTDOOR(adapter);
		if(dword != 0x10001234) {
			/*
			 * No more pending commands
			 */
			goto out_unlock;
		}
		WROUTDOOR(adapter, 0x10001234);

		while((nstatus = (volatile u8)adapter->mbox->m_in.numstatus)
				== 0xFF) {
			cpu_relax();
		}
		adapter->mbox->m_in.numstatus = 0xFF;

		status = adapter->mbox->m_in.status;

		/*
		 * decrement the pending queue counter
		 */
		atomic_sub(nstatus, &adapter->pend_cmds);

		memcpy(completed, (void *)adapter->mbox->m_in.completed, 
				nstatus);

		/* Acknowledge interrupt */
		WRINDOOR(adapter, 0x2);

		handled = 1;

		while( RDINDOOR(adapter) & 0x02 )
			cpu_relax();

		mega_cmd_done(adapter, completed, nstatus, status);

		mega_rundoneq(adapter);

		/* Loop through any pending requests */
		if(atomic_read(&adapter->quiescent) == 0) {
			mega_runpendq(adapter);
		}

	} while(1);

 out_unlock:

	spin_unlock_irqrestore(&adapter->lock, flags);

	return IRQ_RETVAL(handled);
}