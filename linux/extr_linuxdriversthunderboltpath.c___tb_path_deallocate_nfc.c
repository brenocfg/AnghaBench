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
struct tb_path {int path_length; TYPE_1__* hops; int /*<<< orphan*/  nfc_credits; } ;
struct TYPE_2__ {int /*<<< orphan*/  in_port; } ;

/* Variables and functions */
 int tb_port_add_nfc_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_port_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void __tb_path_deallocate_nfc(struct tb_path *path, int first_hop)
{
	int i, res;
	for (i = first_hop; i < path->path_length; i++) {
		res = tb_port_add_nfc_credits(path->hops[i].in_port,
					      -path->nfc_credits);
		if (res)
			tb_port_warn(path->hops[i].in_port,
				     "nfc credits deallocation failed for hop %d\n",
				     i);
	}
}