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
struct ring {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PACKET_RX_RING ; 
 int /*<<< orphan*/  walk_tx (int,struct ring*) ; 
 int /*<<< orphan*/  walk_v3_rx (int,struct ring*) ; 

__attribute__((used)) static void walk_v3(int sock, struct ring *ring)
{
	if (ring->type == PACKET_RX_RING)
		walk_v3_rx(sock, ring);
	else
		walk_tx(sock, ring);
}