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
struct xdp_attachment_info {int /*<<< orphan*/  flags; TYPE_2__* prog; } ;
struct netdev_bpf {int /*<<< orphan*/  prog_flags; int /*<<< orphan*/  prog_id; } ;
struct TYPE_4__ {TYPE_1__* aux; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */

int xdp_attachment_query(struct xdp_attachment_info *info,
			 struct netdev_bpf *bpf)
{
	bpf->prog_id = info->prog ? info->prog->aux->id : 0;
	bpf->prog_flags = info->prog ? info->flags : 0;
	return 0;
}