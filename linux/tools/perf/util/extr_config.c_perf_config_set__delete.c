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
struct perf_config_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct perf_config_set*) ; 
 int /*<<< orphan*/  perf_config_set__purge (struct perf_config_set*) ; 

void perf_config_set__delete(struct perf_config_set *set)
{
	if (set == NULL)
		return;

	perf_config_set__purge(set);
	free(set);
}