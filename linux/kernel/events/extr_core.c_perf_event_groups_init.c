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
struct perf_event_groups {scalar_t__ index; int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT ; 

__attribute__((used)) static void perf_event_groups_init(struct perf_event_groups *groups)
{
	groups->tree = RB_ROOT;
	groups->index = 0;
}