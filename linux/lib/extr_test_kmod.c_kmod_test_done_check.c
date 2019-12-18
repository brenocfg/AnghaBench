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
struct test_config {scalar_t__ num_threads; } ;
struct kmod_test_device {scalar_t__ done; int /*<<< orphan*/  kthreads_done; int /*<<< orphan*/  dev; struct test_config config; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static void kmod_test_done_check(struct kmod_test_device *test_dev,
				 unsigned int idx)
{
	struct test_config *config = &test_dev->config;

	test_dev->done++;
	dev_dbg(test_dev->dev, "Done thread count: %u\n", test_dev->done);

	if (test_dev->done == config->num_threads) {
		dev_info(test_dev->dev, "Done: %u threads have all run now\n",
			 test_dev->done);
		dev_info(test_dev->dev, "Last thread to run: %u\n", idx);
		complete(&test_dev->kthreads_done);
	}
}