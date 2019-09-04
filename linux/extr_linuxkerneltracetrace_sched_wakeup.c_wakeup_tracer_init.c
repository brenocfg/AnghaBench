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
struct trace_array {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int __wakeup_tracer_init (struct trace_array*) ; 
 scalar_t__ wakeup_busy ; 
 scalar_t__ wakeup_dl ; 
 scalar_t__ wakeup_rt ; 

__attribute__((used)) static int wakeup_tracer_init(struct trace_array *tr)
{
	if (wakeup_busy)
		return -EBUSY;

	wakeup_dl = 0;
	wakeup_rt = 0;
	return __wakeup_tracer_init(tr);
}