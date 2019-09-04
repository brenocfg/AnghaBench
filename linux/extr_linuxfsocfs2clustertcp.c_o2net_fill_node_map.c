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
struct o2net_sock_container {int dummy; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  o2net_nn_from_num (int) ; 
 int /*<<< orphan*/  o2net_tx_can_proceed (int /*<<< orphan*/ ,struct o2net_sock_container**,int*) ; 
 int /*<<< orphan*/  sc_put (struct o2net_sock_container*) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

void o2net_fill_node_map(unsigned long *map, unsigned bytes)
{
	struct o2net_sock_container *sc;
	int node, ret;

	BUG_ON(bytes < (BITS_TO_LONGS(O2NM_MAX_NODES) * sizeof(unsigned long)));

	memset(map, 0, bytes);
	for (node = 0; node < O2NM_MAX_NODES; ++node) {
		if (!o2net_tx_can_proceed(o2net_nn_from_num(node), &sc, &ret))
			continue;
		if (!ret) {
			set_bit(node, map);
			sc_put(sc);
		}
	}
}