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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  topo; struct pci_dev* pdev; } ;
struct intel_ntb_dev {int /*<<< orphan*/  db_mask_lock; scalar_t__ db_mask; scalar_t__ db_link_mask; scalar_t__ db_valid_mask; scalar_t__ lnk_sta; scalar_t__ ntb_ctl; scalar_t__ db_vec_shift; scalar_t__ db_vec_count; scalar_t__ db_count; scalar_t__ spad_count; scalar_t__ mw_count; scalar_t__ bar4_split; int /*<<< orphan*/  b2b_idx; scalar_t__ b2b_off; TYPE_1__ ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTB_TOPO_NONE ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  intel_ntb_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ndev_init_struct(struct intel_ntb_dev *ndev,
				    struct pci_dev *pdev)
{
	ndev->ntb.pdev = pdev;
	ndev->ntb.topo = NTB_TOPO_NONE;
	ndev->ntb.ops = &intel_ntb_ops;

	ndev->b2b_off = 0;
	ndev->b2b_idx = UINT_MAX;

	ndev->bar4_split = 0;

	ndev->mw_count = 0;
	ndev->spad_count = 0;
	ndev->db_count = 0;
	ndev->db_vec_count = 0;
	ndev->db_vec_shift = 0;

	ndev->ntb_ctl = 0;
	ndev->lnk_sta = 0;

	ndev->db_valid_mask = 0;
	ndev->db_link_mask = 0;
	ndev->db_mask = 0;

	spin_lock_init(&ndev->db_mask_lock);
}