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
typedef  int /*<<< orphan*/  obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_output_end_data_capture_internal (int /*<<< orphan*/ *,int) ; 

void obs_output_end_data_capture(obs_output_t *output)
{
	obs_output_end_data_capture_internal(output, true);
}