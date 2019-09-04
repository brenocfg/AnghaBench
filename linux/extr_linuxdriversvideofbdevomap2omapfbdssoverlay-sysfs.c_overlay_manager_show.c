#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct omap_overlay {TYPE_1__* manager; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t overlay_manager_show(struct omap_overlay *ovl, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n",
			ovl->manager ? ovl->manager->name : "<none>");
}