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
struct obs_source {scalar_t__ deinterlace_mode; } ;

/* Variables and functions */
 scalar_t__ OBS_DEINTERLACE_MODE_DISABLE ; 

__attribute__((used)) static inline bool deinterlacing_enabled(const struct obs_source *source)
{
	return source->deinterlace_mode != OBS_DEINTERLACE_MODE_DISABLE;
}