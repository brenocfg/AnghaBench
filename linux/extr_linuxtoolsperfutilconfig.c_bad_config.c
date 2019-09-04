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
 scalar_t__ config_file_name ; 
 int /*<<< orphan*/  pr_warning (char*,char const*,...) ; 

__attribute__((used)) static void bad_config(const char *name)
{
	if (config_file_name)
		pr_warning("bad config value for '%s' in %s, ignoring...\n", name, config_file_name);
	else
		pr_warning("bad config value for '%s', ignoring...\n", name);
}