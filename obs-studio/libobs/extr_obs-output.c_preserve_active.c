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
struct obs_output {int delay_flags; } ;

/* Variables and functions */
 int OBS_OUTPUT_DELAY_PRESERVE ; 

__attribute__((used)) static inline bool preserve_active(struct obs_output *output)
{
	return (output->delay_flags & OBS_OUTPUT_DELAY_PRESERVE) != 0;
}