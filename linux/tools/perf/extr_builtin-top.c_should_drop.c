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
struct TYPE_2__ {scalar_t__ type; } ;
union perf_event {TYPE_1__ header; } ;
typedef  scalar_t__ u64 ;
struct perf_top {int delay_secs; } ;
struct ordered_event {scalar_t__ timestamp; union perf_event* event; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 scalar_t__ PERF_RECORD_SAMPLE ; 
 scalar_t__ last_timestamp ; 

__attribute__((used)) static int should_drop(struct ordered_event *qevent, struct perf_top *top)
{
	union perf_event *event = qevent->event;
	u64 delay_timestamp;

	if (event->header.type != PERF_RECORD_SAMPLE)
		return false;

	delay_timestamp = qevent->timestamp + top->delay_secs * NSEC_PER_SEC;
	return delay_timestamp < last_timestamp;
}