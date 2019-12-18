#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct trace_probe {TYPE_1__* event; } ;
struct trace_event_call {int dummy; } ;
struct TYPE_2__ {struct trace_event_call call; } ;

/* Variables and functions */

__attribute__((used)) static inline struct trace_event_call *
	trace_probe_event_call(struct trace_probe *tp)
{
	return &tp->event->call;
}