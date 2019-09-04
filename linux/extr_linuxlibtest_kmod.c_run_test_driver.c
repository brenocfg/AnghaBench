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
struct test_config {scalar_t__ num_threads; scalar_t__ test_driver; int /*<<< orphan*/  test_case; } ;
struct kmod_test_device {int /*<<< orphan*/  dev; struct test_config config; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  test_case_str (int /*<<< orphan*/ ) ; 
 int try_requests (struct kmod_test_device*) ; 

__attribute__((used)) static int run_test_driver(struct kmod_test_device *test_dev)
{
	struct test_config *config = &test_dev->config;

	dev_info(test_dev->dev, "Test case: %s (%u)\n",
		 test_case_str(config->test_case),
		 config->test_case);
	dev_info(test_dev->dev, "Test driver to load: %s\n",
		 config->test_driver);
	dev_info(test_dev->dev, "Number of threads to run: %u\n",
		 config->num_threads);
	dev_info(test_dev->dev, "Thread IDs will range from 0 - %u\n",
		 config->num_threads - 1);

	return try_requests(test_dev);
}