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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t o2hb_heartbeat_mode ; 
 char** o2hb_heartbeat_mode_desc ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t o2hb_heartbeat_group_mode_show(struct config_item *item,
		char *page)
{
	return sprintf(page, "%s\n",
		       o2hb_heartbeat_mode_desc[o2hb_heartbeat_mode]);
}