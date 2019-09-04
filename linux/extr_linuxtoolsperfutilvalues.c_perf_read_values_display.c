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
struct perf_read_values {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  perf_read_values__display_pretty (int /*<<< orphan*/ *,struct perf_read_values*) ; 
 int /*<<< orphan*/  perf_read_values__display_raw (int /*<<< orphan*/ *,struct perf_read_values*) ; 

void perf_read_values_display(FILE *fp, struct perf_read_values *values, int raw)
{
	if (raw)
		perf_read_values__display_raw(fp, values);
	else
		perf_read_values__display_pretty(fp, values);
}