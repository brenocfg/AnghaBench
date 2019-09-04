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
struct test_config {int /*<<< orphan*/  num_threads; } ;
struct kmod_test_device_info {int dummy; } ;
struct kmod_test_device {int /*<<< orphan*/  info; struct test_config config; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  array_size (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_test_dev_info (struct kmod_test_device*) ; 
 int /*<<< orphan*/  vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kmod_config_sync_info(struct kmod_test_device *test_dev)
{
	struct test_config *config = &test_dev->config;

	free_test_dev_info(test_dev);
	test_dev->info =
		vzalloc(array_size(sizeof(struct kmod_test_device_info),
				   config->num_threads));
	if (!test_dev->info)
		return -ENOMEM;

	return 0;
}