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
struct test_config {int /*<<< orphan*/  test_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __kstrncpy (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_copy_test_driver_name(struct test_config *config,
				    const char *name,
				    size_t count)
{
	return __kstrncpy(&config->test_driver, name, count, GFP_KERNEL);
}