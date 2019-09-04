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
struct cfs_overlay_item {char* path; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct cfs_overlay_item* to_cfs_overlay_item (struct config_item*) ; 

__attribute__((used)) static ssize_t cfs_overlay_item_path_show(struct config_item *item,
		char *page)
{
	struct cfs_overlay_item *overlay = to_cfs_overlay_item(item);
	return sprintf(page, "%s\n", overlay->path);
}