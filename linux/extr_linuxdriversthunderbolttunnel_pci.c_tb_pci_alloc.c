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
struct tb_port {struct tb_port* remote; TYPE_2__* sw; } ;
struct tb_pci_tunnel {TYPE_3__* path_to_up; TYPE_3__* path_to_down; int /*<<< orphan*/  list; struct tb_port* up_port; struct tb_port* down_port; struct tb* tb; } ;
struct tb {int dummy; } ;
struct TYPE_7__ {TYPE_1__* hops; } ;
struct TYPE_6__ {int /*<<< orphan*/  tb; } ;
struct TYPE_5__ {int in_hop_index; int in_counter_index; int next_hop_index; struct tb_port* out_port; struct tb_port* in_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tb_pci_tunnel*) ; 
 struct tb_pci_tunnel* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* tb_path_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tb_path_free (TYPE_3__*) ; 
 int /*<<< orphan*/  tb_pci_init_path (TYPE_3__*) ; 
 struct tb_port* tb_upstream_port (TYPE_2__*) ; 

struct tb_pci_tunnel *tb_pci_alloc(struct tb *tb, struct tb_port *up,
				   struct tb_port *down)
{
	struct tb_pci_tunnel *tunnel = kzalloc(sizeof(*tunnel), GFP_KERNEL);
	if (!tunnel)
		goto err;
	tunnel->tb = tb;
	tunnel->down_port = down;
	tunnel->up_port = up;
	INIT_LIST_HEAD(&tunnel->list);
	tunnel->path_to_up = tb_path_alloc(up->sw->tb, 2);
	if (!tunnel->path_to_up)
		goto err;
	tunnel->path_to_down = tb_path_alloc(up->sw->tb, 2);
	if (!tunnel->path_to_down)
		goto err;
	tb_pci_init_path(tunnel->path_to_up);
	tb_pci_init_path(tunnel->path_to_down);

	tunnel->path_to_up->hops[0].in_port = down;
	tunnel->path_to_up->hops[0].in_hop_index = 8;
	tunnel->path_to_up->hops[0].in_counter_index = -1;
	tunnel->path_to_up->hops[0].out_port = tb_upstream_port(up->sw)->remote;
	tunnel->path_to_up->hops[0].next_hop_index = 8;

	tunnel->path_to_up->hops[1].in_port = tb_upstream_port(up->sw);
	tunnel->path_to_up->hops[1].in_hop_index = 8;
	tunnel->path_to_up->hops[1].in_counter_index = -1;
	tunnel->path_to_up->hops[1].out_port = up;
	tunnel->path_to_up->hops[1].next_hop_index = 8;

	tunnel->path_to_down->hops[0].in_port = up;
	tunnel->path_to_down->hops[0].in_hop_index = 8;
	tunnel->path_to_down->hops[0].in_counter_index = -1;
	tunnel->path_to_down->hops[0].out_port = tb_upstream_port(up->sw);
	tunnel->path_to_down->hops[0].next_hop_index = 8;

	tunnel->path_to_down->hops[1].in_port =
		tb_upstream_port(up->sw)->remote;
	tunnel->path_to_down->hops[1].in_hop_index = 8;
	tunnel->path_to_down->hops[1].in_counter_index = -1;
	tunnel->path_to_down->hops[1].out_port = down;
	tunnel->path_to_down->hops[1].next_hop_index = 8;
	return tunnel;

err:
	if (tunnel) {
		if (tunnel->path_to_down)
			tb_path_free(tunnel->path_to_down);
		if (tunnel->path_to_up)
			tb_path_free(tunnel->path_to_up);
		kfree(tunnel);
	}
	return NULL;
}