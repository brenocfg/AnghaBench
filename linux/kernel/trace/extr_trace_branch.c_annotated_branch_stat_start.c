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
struct tracer_stat {int dummy; } ;

/* Variables and functions */
 void* __start_annotated_branch_profile ; 

__attribute__((used)) static void *annotated_branch_stat_start(struct tracer_stat *trace)
{
	return __start_annotated_branch_profile;
}