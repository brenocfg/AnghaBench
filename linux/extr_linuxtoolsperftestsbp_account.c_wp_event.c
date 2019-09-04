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
struct perf_event_attr {int dummy; } ;

/* Variables and functions */
 int __event (int,void*,struct perf_event_attr*) ; 

__attribute__((used)) static int wp_event(void *addr, struct perf_event_attr *attr)
{
	return __event(false, addr, attr);
}