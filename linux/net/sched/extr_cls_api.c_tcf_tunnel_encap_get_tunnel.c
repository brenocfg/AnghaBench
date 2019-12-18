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
struct tc_action {int dummy; } ;
struct flow_action_entry {scalar_t__ tunnel; scalar_t__ destructor_priv; int /*<<< orphan*/  destructor; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  tcf_tunnel_encap_put_tunnel ; 
 scalar_t__ tcf_tunnel_info_copy (struct tc_action const*) ; 

__attribute__((used)) static int tcf_tunnel_encap_get_tunnel(struct flow_action_entry *entry,
				       const struct tc_action *act)
{
	entry->tunnel = tcf_tunnel_info_copy(act);
	if (!entry->tunnel)
		return -ENOMEM;
	entry->destructor = tcf_tunnel_encap_put_tunnel;
	entry->destructor_priv = entry->tunnel;
	return 0;
}