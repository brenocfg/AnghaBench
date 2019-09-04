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
struct obs_output {int /*<<< orphan*/  end_data_capture_thread_active; } ;

/* Variables and functions */
 int os_atomic_load_bool (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool data_capture_ending(const struct obs_output *output)
{
	return os_atomic_load_bool(&output->end_data_capture_thread_active);
}