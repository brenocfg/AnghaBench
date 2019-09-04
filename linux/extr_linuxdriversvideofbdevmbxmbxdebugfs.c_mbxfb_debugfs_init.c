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
struct mbxfb_debugfs_data {int /*<<< orphan*/  dir; void* misc; void* sdram; void* gsctl; void* display; void* clock; void* sysconf; } ;
struct fb_info {struct mbxfb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clock_fops ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 void* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct fb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_fops ; 
 int /*<<< orphan*/  gsctl_fops ; 
 struct mbxfb_debugfs_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_fops ; 
 int /*<<< orphan*/  sdram_fops ; 
 int /*<<< orphan*/  sysconf_fops ; 

__attribute__((used)) static void mbxfb_debugfs_init(struct fb_info *fbi)
{
	struct mbxfb_info *mfbi = fbi->par;
	struct mbxfb_debugfs_data *dbg;

	dbg = kzalloc(sizeof(struct mbxfb_debugfs_data), GFP_KERNEL);
	mfbi->debugfs_data = dbg;

	dbg->dir = debugfs_create_dir("mbxfb", NULL);
	dbg->sysconf = debugfs_create_file("sysconf", 0444, dbg->dir,
				      fbi, &sysconf_fops);
	dbg->clock = debugfs_create_file("clock", 0444, dbg->dir,
				    fbi, &clock_fops);
	dbg->display = debugfs_create_file("display", 0444, dbg->dir,
				      fbi, &display_fops);
	dbg->gsctl = debugfs_create_file("gsctl", 0444, dbg->dir,
				    fbi, &gsctl_fops);
	dbg->sdram = debugfs_create_file("sdram", 0444, dbg->dir,
					fbi, &sdram_fops);
	dbg->misc = debugfs_create_file("misc", 0444, dbg->dir,
					fbi, &misc_fops);
}