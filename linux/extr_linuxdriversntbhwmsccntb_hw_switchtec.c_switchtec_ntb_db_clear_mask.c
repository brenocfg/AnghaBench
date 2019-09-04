#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct switchtec_ntb {int db_valid_mask; int db_mask; int db_shift; int /*<<< orphan*/  db_mask_lock; TYPE_1__* mmio_self_dbmsg; } ;
struct ntb_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  idb_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  iowrite64 (int,int /*<<< orphan*/ *) ; 
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int switchtec_ntb_db_clear_mask(struct ntb_dev *ntb, u64 db_bits)
{
	unsigned long irqflags;
	struct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (db_bits & ~sndev->db_valid_mask)
		return -EINVAL;

	spin_lock_irqsave(&sndev->db_mask_lock, irqflags);

	sndev->db_mask &= ~(db_bits << sndev->db_shift);
	iowrite64(~sndev->db_mask, &sndev->mmio_self_dbmsg->idb_mask);

	spin_unlock_irqrestore(&sndev->db_mask_lock, irqflags);

	return 0;
}