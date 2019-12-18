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
struct o2hb_heartbeat_group {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct o2hb_heartbeat_group*) ; 
 struct o2hb_heartbeat_group* to_o2hb_heartbeat_group (struct config_group*) ; 

void o2hb_free_hb_set(struct config_group *group)
{
	struct o2hb_heartbeat_group *hs = to_o2hb_heartbeat_group(group);
	kfree(hs);
}