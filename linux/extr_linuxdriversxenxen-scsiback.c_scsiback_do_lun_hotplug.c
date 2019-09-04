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
struct vscsibk_info {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char**) ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  kfree (char**) ; 
 int /*<<< orphan*/  scsiback_do_1lun_hotplug (struct vscsibk_info*,int,char*) ; 
 char** xenbus_directory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int*) ; 

__attribute__((used)) static void scsiback_do_lun_hotplug(struct vscsibk_info *info, int op)
{
	int i;
	char **dir;
	unsigned int ndir = 0;

	dir = xenbus_directory(XBT_NIL, info->dev->nodename, "vscsi-devs",
			       &ndir);
	if (IS_ERR(dir))
		return;

	for (i = 0; i < ndir; i++)
		scsiback_do_1lun_hotplug(info, op, dir[i]);

	kfree(dir);
}