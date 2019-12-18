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
struct net_bridge {int /*<<< orphan*/  options; } ;
typedef  enum net_bridge_opts { ____Placeholder_net_bridge_opts } net_bridge_opts ;

/* Variables and functions */
 int /*<<< orphan*/  br_debug (struct net_bridge*,char*,int,int,int) ; 
 int /*<<< orphan*/  br_opt_get (struct net_bridge*,int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

void br_opt_toggle(struct net_bridge *br, enum net_bridge_opts opt, bool on)
{
	bool cur = !!br_opt_get(br, opt);

	br_debug(br, "toggle option: %d state: %d -> %d\n",
		 opt, cur, on);

	if (cur == on)
		return;

	if (on)
		set_bit(opt, &br->options);
	else
		clear_bit(opt, &br->options);
}