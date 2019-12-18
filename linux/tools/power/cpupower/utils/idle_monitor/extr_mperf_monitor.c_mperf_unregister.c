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
 int /*<<< orphan*/  aperf_current_count ; 
 int /*<<< orphan*/  aperf_previous_count ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid ; 
 int /*<<< orphan*/  mperf_current_count ; 
 int /*<<< orphan*/  mperf_previous_count ; 

void mperf_unregister(void)
{
	free(mperf_previous_count);
	free(aperf_previous_count);
	free(mperf_current_count);
	free(aperf_current_count);
	free(is_valid);
}