#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device* parent; } ;
struct regulator_dev {int /*<<< orphan*/  bypass_count; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  open_count; int /*<<< orphan*/  use_count; TYPE_2__* desc; TYPE_1__ dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {char const* name; } ;

/* Variables and functions */
 int NAME_MAX ; 
 int /*<<< orphan*/  debugfs_create_dir (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_root ; 
 char* dev_name (struct device*) ; 
 char* rdev_get_name (struct regulator_dev*) ; 
 int /*<<< orphan*/  rdev_warn (struct regulator_dev*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static void rdev_init_debugfs(struct regulator_dev *rdev)
{
	struct device *parent = rdev->dev.parent;
	const char *rname = rdev_get_name(rdev);
	char name[NAME_MAX];

	/* Avoid duplicate debugfs directory names */
	if (parent && rname == rdev->desc->name) {
		snprintf(name, sizeof(name), "%s-%s", dev_name(parent),
			 rname);
		rname = name;
	}

	rdev->debugfs = debugfs_create_dir(rname, debugfs_root);
	if (!rdev->debugfs) {
		rdev_warn(rdev, "Failed to create debugfs directory\n");
		return;
	}

	debugfs_create_u32("use_count", 0444, rdev->debugfs,
			   &rdev->use_count);
	debugfs_create_u32("open_count", 0444, rdev->debugfs,
			   &rdev->open_count);
	debugfs_create_u32("bypass_count", 0444, rdev->debugfs,
			   &rdev->bypass_count);
}