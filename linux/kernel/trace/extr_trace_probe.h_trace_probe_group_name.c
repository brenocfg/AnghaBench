#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct trace_probe {TYPE_3__* event; } ;
struct TYPE_5__ {TYPE_1__* class; } ;
struct TYPE_6__ {TYPE_2__ call; } ;
struct TYPE_4__ {char const* system; } ;

/* Variables and functions */

__attribute__((used)) static inline const char *trace_probe_group_name(struct trace_probe *tp)
{
	return tp->event->call.class->system;
}