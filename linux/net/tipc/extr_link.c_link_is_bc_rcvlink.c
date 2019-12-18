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
struct tipc_link {struct tipc_link* bc_rcvlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  link_is_bc_sndlink (struct tipc_link*) ; 

__attribute__((used)) static bool link_is_bc_rcvlink(struct tipc_link *l)
{
	return ((l->bc_rcvlink == l) && !link_is_bc_sndlink(l));
}