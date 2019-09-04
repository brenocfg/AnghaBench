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
struct tipc_peer {int /*<<< orphan*/  is_head; } ;

/* Variables and functions */
 struct tipc_peer* peer_prev (struct tipc_peer*) ; 

__attribute__((used)) static struct tipc_peer *peer_head(struct tipc_peer *peer)
{
	while (!peer->is_head)
		peer = peer_prev(peer);
	return peer;
}