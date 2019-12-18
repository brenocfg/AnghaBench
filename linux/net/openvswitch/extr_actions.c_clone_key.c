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
struct sw_flow_key {int dummy; } ;
struct action_flow_keys {struct sw_flow_key* key; } ;

/* Variables and functions */
 int OVS_DEFERRED_ACTION_THRESHOLD ; 
 int /*<<< orphan*/  exec_actions_level ; 
 int /*<<< orphan*/  flow_keys ; 
 struct action_flow_keys* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sw_flow_key *clone_key(const struct sw_flow_key *key_)
{
	struct action_flow_keys *keys = this_cpu_ptr(flow_keys);
	int level = this_cpu_read(exec_actions_level);
	struct sw_flow_key *key = NULL;

	if (level <= OVS_DEFERRED_ACTION_THRESHOLD) {
		key = &keys->key[level - 1];
		*key = *key_;
	}

	return key;
}