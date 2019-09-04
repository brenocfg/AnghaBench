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
 int /*<<< orphan*/ * config_set ; 
 int /*<<< orphan*/ * perf_config_set__new () ; 

__attribute__((used)) static int perf_config__init(void)
{
	if (config_set == NULL)
		config_set = perf_config_set__new();

	return config_set == NULL;
}