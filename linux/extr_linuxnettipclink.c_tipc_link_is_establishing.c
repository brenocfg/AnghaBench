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
struct tipc_link {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ LINK_ESTABLISHING ; 

bool tipc_link_is_establishing(struct tipc_link *l)
{
	return l->state == LINK_ESTABLISHING;
}