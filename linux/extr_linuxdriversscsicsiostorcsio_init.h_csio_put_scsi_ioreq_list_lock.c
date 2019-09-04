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
struct list_head {int dummy; } ;
struct csio_scsim {int /*<<< orphan*/  freelist_lock; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  csio_put_scsi_ioreq_list (struct csio_scsim*,struct list_head*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void
csio_put_scsi_ioreq_list_lock(struct csio_hw *hw, struct csio_scsim *scsim,
			      struct list_head *reqlist, int n)
{
	unsigned long flags;

	spin_lock_irqsave(&scsim->freelist_lock, flags);
	csio_put_scsi_ioreq_list(scsim, reqlist, n);
	spin_unlock_irqrestore(&scsim->freelist_lock, flags);
}