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
 int TRACE_RECORD_CMDLINE ; 
 int TRACE_RECORD_TGID ; 
 int /*<<< orphan*/  __this_cpu_read (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_record_taskinfo_disabled ; 
 int /*<<< orphan*/  trace_taskinfo_save ; 
 int /*<<< orphan*/  tracing_is_on () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool tracing_record_taskinfo_skip(int flags)
{
	if (unlikely(!(flags & (TRACE_RECORD_CMDLINE | TRACE_RECORD_TGID))))
		return true;
	if (atomic_read(&trace_record_taskinfo_disabled) || !tracing_is_on())
		return true;
	if (!__this_cpu_read(trace_taskinfo_save))
		return true;
	return false;
}