#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pyrf_event {TYPE_2__* evsel; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;

/* Variables and functions */
 scalar_t__ PERF_TYPE_TRACEPOINT ; 

__attribute__((used)) static bool is_tracepoint(struct pyrf_event *pevent)
{
	return pevent->evsel->attr.type == PERF_TYPE_TRACEPOINT;
}