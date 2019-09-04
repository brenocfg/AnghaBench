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
struct tb_regs_hop {int dummy; } ;
struct tb_path {int path_length; TYPE_1__* hops; } ;
struct TYPE_2__ {int in_hop_index; int /*<<< orphan*/  in_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_HOPS ; 
 int /*<<< orphan*/  tb_port_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int tb_port_write (int /*<<< orphan*/ ,struct tb_regs_hop*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void __tb_path_deactivate_hops(struct tb_path *path, int first_hop)
{
	int i, res;
	struct tb_regs_hop hop = { };
	for (i = first_hop; i < path->path_length; i++) {
		res = tb_port_write(path->hops[i].in_port, &hop, TB_CFG_HOPS,
				    2 * path->hops[i].in_hop_index, 2);
		if (res)
			tb_port_warn(path->hops[i].in_port,
				     "hop deactivation failed for hop %d, index %d\n",
				     i, path->hops[i].in_hop_index);
	}
}