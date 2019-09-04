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
typedef  int u64 ;
struct TYPE_3__ {int /*<<< orphan*/  topo; } ;
struct switchtec_ntb {int* direct_mw_to_bar; int nr_direct_mw; int peer_partition; int /*<<< orphan*/  nr_rsvd_luts; scalar_t__ mmio_xlink_win; scalar_t__ mmio_peer_dbmsg; TYPE_2__* stdev; int /*<<< orphan*/  mmio_peer_ctrl; int /*<<< orphan*/  mmio_self_ctrl; TYPE_1__ ntb; } ;
struct ntb_dbmsg_regs {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int LUT_SIZE ; 
 int /*<<< orphan*/  NTB_TOPO_CROSSLINK ; 
 int SWITCHTEC_GAS_NTB_OFFSET ; 
 int SWITCHTEC_NTB_REG_DBMSG_OFFSET ; 
 int config_rsvd_lut_win (struct switchtec_ntb*,int /*<<< orphan*/ ,int const,int,int) ; 
 int crosslink_enum_partition (struct switchtec_ntb*,int*) ; 
 int /*<<< orphan*/  crosslink_init_dbmsgs (struct switchtec_ntb*) ; 
 int /*<<< orphan*/  crosslink_is_enabled (struct switchtec_ntb*) ; 
 int crosslink_setup_mws (struct switchtec_ntb*,int const,int*,int) ; 
 int crosslink_setup_req_ids (struct switchtec_ntb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pci_iomap_range (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int switchtec_ntb_init_crosslink(struct switchtec_ntb *sndev)
{
	int rc;
	int bar = sndev->direct_mw_to_bar[0];
	const int ntb_lut_idx = 1;
	u64 bar_addrs[6];
	u64 addr;
	int offset;
	int bar_cnt;

	if (!crosslink_is_enabled(sndev))
		return 0;

	dev_info(&sndev->stdev->dev, "Using crosslink configuration\n");
	sndev->ntb.topo = NTB_TOPO_CROSSLINK;

	bar_cnt = crosslink_enum_partition(sndev, bar_addrs);
	if (bar_cnt < sndev->nr_direct_mw + 1) {
		dev_err(&sndev->stdev->dev,
			"Error enumerating crosslink partition\n");
		return -EINVAL;
	}

	addr = (bar_addrs[0] + SWITCHTEC_GAS_NTB_OFFSET +
		SWITCHTEC_NTB_REG_DBMSG_OFFSET +
		sizeof(struct ntb_dbmsg_regs) * sndev->peer_partition);

	offset = addr & (LUT_SIZE - 1);
	addr -= offset;

	rc = config_rsvd_lut_win(sndev, sndev->mmio_self_ctrl, ntb_lut_idx,
				 sndev->peer_partition, addr);
	if (rc)
		return rc;

	rc = crosslink_setup_mws(sndev, ntb_lut_idx, &bar_addrs[1],
				 bar_cnt - 1);
	if (rc)
		return rc;

	rc = crosslink_setup_req_ids(sndev, sndev->mmio_peer_ctrl);
	if (rc)
		return rc;

	sndev->mmio_xlink_win = pci_iomap_range(sndev->stdev->pdev, bar,
						LUT_SIZE, LUT_SIZE);
	if (!sndev->mmio_xlink_win) {
		rc = -ENOMEM;
		return rc;
	}

	sndev->mmio_peer_dbmsg = sndev->mmio_xlink_win + offset;
	sndev->nr_rsvd_luts++;

	crosslink_init_dbmsgs(sndev);

	return 0;
}