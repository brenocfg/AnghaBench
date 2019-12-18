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
 scalar_t__ get_frame_size () ; 
 int maybe_ge (scalar_t__,scalar_t__) ; 
 scalar_t__ track_frame_size ; 

__attribute__((used)) static bool large_stack_frame(void)
{
#if BUILDING_GCC_VERSION >= 8000
	return maybe_ge(get_frame_size(), track_frame_size);
#else
	return (get_frame_size() >= track_frame_size);
#endif
}