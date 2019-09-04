#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_7__ {TYPE_1__* pdev; } ;
struct intel_ntb_dev {int hwerr_flags; int db_link_mask; int db_valid_mask; TYPE_3__ ntb; TYPE_2__* reg; int /*<<< orphan*/  last_ts; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {scalar_t__ (* poll_link ) (struct intel_ntb_dev*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int NTB_HWERR_MSIX_VECTOR32_BAD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int ndev_vec_mask (struct intel_ntb_dev*,int) ; 
 int /*<<< orphan*/  ntb_db_event (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ntb_link_event (TYPE_3__*) ; 
 scalar_t__ stub1 (struct intel_ntb_dev*) ; 

__attribute__((used)) static irqreturn_t ndev_interrupt(struct intel_ntb_dev *ndev, int vec)
{
	u64 vec_mask;

	vec_mask = ndev_vec_mask(ndev, vec);

	if ((ndev->hwerr_flags & NTB_HWERR_MSIX_VECTOR32_BAD) && (vec == 31))
		vec_mask |= ndev->db_link_mask;

	dev_dbg(&ndev->ntb.pdev->dev, "vec %d vec_mask %llx\n", vec, vec_mask);

	ndev->last_ts = jiffies;

	if (vec_mask & ndev->db_link_mask) {
		if (ndev->reg->poll_link(ndev))
			ntb_link_event(&ndev->ntb);
	}

	if (vec_mask & ndev->db_valid_mask)
		ntb_db_event(&ndev->ntb, vec);

	return IRQ_HANDLED;
}