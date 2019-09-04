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
struct cros_ec_platform {char* ec_name; } ;
struct cros_ec_dev {struct cros_ec_debugfs* debug_info; int /*<<< orphan*/  dev; } ;
struct cros_ec_debugfs {int /*<<< orphan*/  dir; struct cros_ec_dev* ec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cros_ec_create_console_log (struct cros_ec_debugfs*) ; 
 int cros_ec_create_panicinfo (struct cros_ec_debugfs*) ; 
 int cros_ec_create_pdinfo (struct cros_ec_debugfs*) ; 
 int /*<<< orphan*/  debugfs_create_dir (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct cros_ec_platform* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct cros_ec_debugfs* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int cros_ec_debugfs_init(struct cros_ec_dev *ec)
{
	struct cros_ec_platform *ec_platform = dev_get_platdata(ec->dev);
	const char *name = ec_platform->ec_name;
	struct cros_ec_debugfs *debug_info;
	int ret;

	debug_info = devm_kzalloc(ec->dev, sizeof(*debug_info), GFP_KERNEL);
	if (!debug_info)
		return -ENOMEM;

	debug_info->ec = ec;
	debug_info->dir = debugfs_create_dir(name, NULL);
	if (!debug_info->dir)
		return -ENOMEM;

	ret = cros_ec_create_panicinfo(debug_info);
	if (ret)
		goto remove_debugfs;

	ret = cros_ec_create_console_log(debug_info);
	if (ret)
		goto remove_debugfs;

	ret = cros_ec_create_pdinfo(debug_info);
	if (ret)
		goto remove_debugfs;

	ec->debug_info = debug_info;

	return 0;

remove_debugfs:
	debugfs_remove_recursive(debug_info->dir);
	return ret;
}