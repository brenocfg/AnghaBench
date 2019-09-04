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
struct cros_ec_debugfs {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cros_ec_pdinfo_fops ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct cros_ec_debugfs*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_create_pdinfo(struct cros_ec_debugfs *debug_info)
{
	if (!debugfs_create_file("pdinfo", 0444, debug_info->dir, debug_info,
				 &cros_ec_pdinfo_fops))
		return -ENOMEM;

	return 0;
}