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
struct xdp_attachment_info {int /*<<< orphan*/  flags; scalar_t__ prog; } ;
struct netdev_bpf {int /*<<< orphan*/  flags; scalar_t__ prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_put (scalar_t__) ; 

void xdp_attachment_setup(struct xdp_attachment_info *info,
			  struct netdev_bpf *bpf)
{
	if (info->prog)
		bpf_prog_put(info->prog);
	info->prog = bpf->prog;
	info->flags = bpf->flags;
}