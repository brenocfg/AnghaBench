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
struct TYPE_2__ {int mode; int /*<<< orphan*/  name; } ;
struct batadv_debuginfo {int /*<<< orphan*/  fops; TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DEBUGFS_SUBDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  batadv_debugfs ; 
 struct batadv_debuginfo** batadv_general_debuginfos ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void batadv_debugfs_init(void)
{
	struct batadv_debuginfo **bat_debug;

	batadv_debugfs = debugfs_create_dir(BATADV_DEBUGFS_SUBDIR, NULL);

	for (bat_debug = batadv_general_debuginfos; *bat_debug; ++bat_debug)
		debugfs_create_file(((*bat_debug)->attr).name,
				    S_IFREG | ((*bat_debug)->attr).mode,
				    batadv_debugfs, NULL, &(*bat_debug)->fops);
}