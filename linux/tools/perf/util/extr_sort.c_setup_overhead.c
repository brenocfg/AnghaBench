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
struct TYPE_2__ {scalar_t__ cumulate_callchain; } ;

/* Variables and functions */
 scalar_t__ SORT_MODE__DIFF ; 
 char* prefix_if_not_in (char*,char*) ; 
 scalar_t__ sort__mode ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static char *setup_overhead(char *keys)
{
	if (sort__mode == SORT_MODE__DIFF)
		return keys;

	keys = prefix_if_not_in("overhead", keys);

	if (symbol_conf.cumulate_callchain)
		keys = prefix_if_not_in("overhead_children", keys);

	return keys;
}