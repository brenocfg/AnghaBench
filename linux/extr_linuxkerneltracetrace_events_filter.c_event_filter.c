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
struct trace_event_file {struct event_filter* filter; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct event_filter *event_filter(struct trace_event_file *file)
{
	return file->filter;
}