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

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_fl_gc_timer ; 
 int /*<<< orphan*/  ip6_flowlabel_net_ops ; 
 int /*<<< orphan*/  unregister_pernet_subsys (int /*<<< orphan*/ *) ; 

void ip6_flowlabel_cleanup(void)
{
	del_timer(&ip6_fl_gc_timer);
	unregister_pernet_subsys(&ip6_flowlabel_net_ops);
}