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
 int /*<<< orphan*/  perf_config_set__delete (int /*<<< orphan*/ *) ; 

void perf_config__exit(void)
{
	perf_config_set__delete(config_set);
	config_set = NULL;
}