#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fib {int size; int /*<<< orphan*/ * callback_data; int /*<<< orphan*/ * callback; int /*<<< orphan*/  flags; TYPE_2__* hw_fib_va; int /*<<< orphan*/  type; struct fib* next; } ;
struct aac_dev {int /*<<< orphan*/  fib_lock; struct fib* free_fib; } ;
struct TYPE_3__ {scalar_t__ XferState; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSAFS_NTC_FIB_CONTEXT ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct fib *aac_fib_alloc(struct aac_dev *dev)
{
	struct fib * fibptr;
	unsigned long flags;
	spin_lock_irqsave(&dev->fib_lock, flags);
	fibptr = dev->free_fib;
	if(!fibptr){
		spin_unlock_irqrestore(&dev->fib_lock, flags);
		return fibptr;
	}
	dev->free_fib = fibptr->next;
	spin_unlock_irqrestore(&dev->fib_lock, flags);
	/*
	 *	Set the proper node type code and node byte size
	 */
	fibptr->type = FSAFS_NTC_FIB_CONTEXT;
	fibptr->size = sizeof(struct fib);
	/*
	 *	Null out fields that depend on being zero at the start of
	 *	each I/O
	 */
	fibptr->hw_fib_va->header.XferState = 0;
	fibptr->flags = 0;
	fibptr->callback = NULL;
	fibptr->callback_data = NULL;

	return fibptr;
}