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
struct ntb_dev {int dummy; } ;
struct idt_ntb_peer {int mw_cnt; TYPE_1__* mws; } ;
struct idt_ntb_dev {int peer_cnt; struct idt_ntb_peer* peers; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  size_max; int /*<<< orphan*/  size_align; int /*<<< orphan*/  addr_align; } ;

/* Variables and functions */
 int EINVAL ; 
 struct idt_ntb_dev* to_ndev_ntb (struct ntb_dev*) ; 

__attribute__((used)) static int idt_ntb_mw_get_align(struct ntb_dev *ntb, int pidx, int widx,
				resource_size_t *addr_align,
				resource_size_t *size_align,
				resource_size_t *size_max)
{
	struct idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	struct idt_ntb_peer *peer;

	if (pidx < 0 || ndev->peer_cnt <= pidx)
		return -EINVAL;

	peer = &ndev->peers[pidx];

	if (widx < 0 || peer->mw_cnt <= widx)
		return -EINVAL;

	if (addr_align != NULL)
		*addr_align = peer->mws[widx].addr_align;

	if (size_align != NULL)
		*size_align = peer->mws[widx].size_align;

	if (size_max != NULL)
		*size_max = peer->mws[widx].size_max;

	return 0;
}