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
 int /*<<< orphan*/  ESCAPE_CODE ; 
 int /*<<< orphan*/  TRACE_BEGIN_CODE ; 
 int /*<<< orphan*/  add_event_entry (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_trace_begin(void)
{
	add_event_entry(ESCAPE_CODE);
	add_event_entry(TRACE_BEGIN_CODE);
}