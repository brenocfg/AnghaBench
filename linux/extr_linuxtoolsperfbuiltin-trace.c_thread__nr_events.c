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
struct thread_trace {unsigned long nr_events; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long thread__nr_events(struct thread_trace *ttrace)
{
	return ttrace ? ttrace->nr_events : 0;
}