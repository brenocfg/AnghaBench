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
struct trace_event_file {int /*<<< orphan*/ * filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_filter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __free_subsystem_filter(struct trace_event_file *file)
{
	__free_filter(file->filter);
	file->filter = NULL;
}