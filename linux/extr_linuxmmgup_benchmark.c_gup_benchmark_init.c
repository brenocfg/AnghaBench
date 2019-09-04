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

/* Variables and functions */
 void* debugfs_create_file_unsafe (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gup_benchmark_fops ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int gup_benchmark_init(void)
{
	void *ret;

	ret = debugfs_create_file_unsafe("gup_benchmark", 0600, NULL, NULL,
			&gup_benchmark_fops);
	if (!ret)
		pr_warn("Failed to create gup_benchmark in debugfs");

	return 0;
}