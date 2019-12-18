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
struct xdp_attachment_info {int flags; scalar_t__ prog; } ;
struct netdev_bpf {int flags; int /*<<< orphan*/  extack; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_SET_ERR_MSG (int /*<<< orphan*/ ,char*) ; 
 int XDP_FLAGS_MODES ; 

bool xdp_attachment_flags_ok(struct xdp_attachment_info *info,
			     struct netdev_bpf *bpf)
{
	if (info->prog && (bpf->flags ^ info->flags) & XDP_FLAGS_MODES) {
		NL_SET_ERR_MSG(bpf->extack,
			       "program loaded with different flags");
		return false;
	}
	return true;
}