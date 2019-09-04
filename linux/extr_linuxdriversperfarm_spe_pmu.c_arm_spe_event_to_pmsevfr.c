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
typedef  int /*<<< orphan*/  u64 ;
struct perf_event_attr {int dummy; } ;
struct perf_event {struct perf_event_attr attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CFG_GET_FLD (struct perf_event_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_filter ; 

__attribute__((used)) static u64 arm_spe_event_to_pmsevfr(struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	return ATTR_CFG_GET_FLD(attr, event_filter);
}