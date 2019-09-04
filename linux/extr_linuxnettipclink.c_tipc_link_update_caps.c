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
typedef  int /*<<< orphan*/  u16 ;
struct tipc_link {int /*<<< orphan*/  peer_caps; } ;

/* Variables and functions */

void tipc_link_update_caps(struct tipc_link *l, u16 capabilities)
{
	l->peer_caps = capabilities;
}