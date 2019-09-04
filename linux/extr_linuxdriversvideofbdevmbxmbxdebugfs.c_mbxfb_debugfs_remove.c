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
struct mbxfb_info {struct mbxfb_debugfs_data* debugfs_data; } ;
struct mbxfb_debugfs_data {int /*<<< orphan*/  dir; int /*<<< orphan*/  sysconf; int /*<<< orphan*/  clock; int /*<<< orphan*/  display; int /*<<< orphan*/  gsctl; int /*<<< orphan*/  sdram; int /*<<< orphan*/  misc; } ;
struct fb_info {struct mbxfb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mbxfb_debugfs_remove(struct fb_info *fbi)
{
	struct mbxfb_info *mfbi = fbi->par;
	struct mbxfb_debugfs_data *dbg = mfbi->debugfs_data;

	debugfs_remove(dbg->misc);
	debugfs_remove(dbg->sdram);
	debugfs_remove(dbg->gsctl);
	debugfs_remove(dbg->display);
	debugfs_remove(dbg->clock);
	debugfs_remove(dbg->sysconf);
	debugfs_remove(dbg->dir);
}