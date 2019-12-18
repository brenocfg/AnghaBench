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
struct test_config {int /*<<< orphan*/ * test_fs; int /*<<< orphan*/ * test_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __kmod_config_free(struct test_config *config)
{
	if (!config)
		return;

	kfree_const(config->test_driver);
	config->test_driver = NULL;

	kfree_const(config->test_fs);
	config->test_fs = NULL;
}