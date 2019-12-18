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
struct config_group {int dummy; } ;
struct o2hb_heartbeat_group {struct config_group hs_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct o2hb_heartbeat_group*) ; 
 struct o2hb_heartbeat_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2hb_heartbeat_group_type ; 

struct config_group *o2hb_alloc_hb_set(void)
{
	struct o2hb_heartbeat_group *hs = NULL;
	struct config_group *ret = NULL;

	hs = kzalloc(sizeof(struct o2hb_heartbeat_group), GFP_KERNEL);
	if (hs == NULL)
		goto out;

	config_group_init_type_name(&hs->hs_group, "heartbeat",
				    &o2hb_heartbeat_group_type);

	ret = &hs->hs_group;
out:
	if (ret == NULL)
		kfree(hs);
	return ret;
}