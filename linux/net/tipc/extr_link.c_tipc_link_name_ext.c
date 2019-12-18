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
struct tipc_link {int /*<<< orphan*/  name; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_MAX_LINK_NAME ; 
 scalar_t__ link_is_bc_rcvlink (struct tipc_link*) ; 
 scalar_t__ link_is_bc_sndlink (struct tipc_link*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

char *tipc_link_name_ext(struct tipc_link *l, char *buf)
{
	if (!l)
		scnprintf(buf, TIPC_MAX_LINK_NAME, "null");
	else if (link_is_bc_sndlink(l))
		scnprintf(buf, TIPC_MAX_LINK_NAME, "broadcast-sender");
	else if (link_is_bc_rcvlink(l))
		scnprintf(buf, TIPC_MAX_LINK_NAME,
			  "broadcast-receiver, peer %x", l->addr);
	else
		memcpy(buf, l->name, TIPC_MAX_LINK_NAME);

	return buf;
}