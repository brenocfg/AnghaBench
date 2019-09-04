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
struct idt_ntb_peer {void* mws; int /*<<< orphan*/  port; int /*<<< orphan*/  mw_cnt; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct idt_ntb_dev {unsigned char peer_cnt; TYPE_2__ ntb; int /*<<< orphan*/  lut_lock; struct idt_ntb_peer* peers; void* mws; int /*<<< orphan*/  port; int /*<<< orphan*/  mw_cnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* idt_scan_mws (struct idt_ntb_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idt_init_mws(struct idt_ntb_dev *ndev)
{
	struct idt_ntb_peer *peer;
	unsigned char pidx;

	/* Scan memory windows of the local port */
	ndev->mws = idt_scan_mws(ndev, ndev->port, &ndev->mw_cnt);
	if (IS_ERR(ndev->mws)) {
		dev_err(&ndev->ntb.pdev->dev,
			"Failed to scan mws of local port %hhu", ndev->port);
		return PTR_ERR(ndev->mws);
	}

	/* Scan memory windows of the peer ports */
	for (pidx = 0; pidx < ndev->peer_cnt; pidx++) {
		peer = &ndev->peers[pidx];
		peer->mws = idt_scan_mws(ndev, peer->port, &peer->mw_cnt);
		if (IS_ERR(peer->mws)) {
			dev_err(&ndev->ntb.pdev->dev,
				"Failed to scan mws of port %hhu", peer->port);
			return PTR_ERR(peer->mws);
		}
	}

	/* Initialize spin locker of the LUT registers */
	spin_lock_init(&ndev->lut_lock);

	dev_dbg(&ndev->ntb.pdev->dev, "Outbound and inbound MWs initialized");

	return 0;
}