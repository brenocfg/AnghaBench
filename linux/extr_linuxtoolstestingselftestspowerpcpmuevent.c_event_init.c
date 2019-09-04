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
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_TYPE_RAW ; 
 int /*<<< orphan*/  event_init_opts (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void event_init(struct event *e, u64 config)
{
	event_init_opts(e, config, PERF_TYPE_RAW, "event");
}