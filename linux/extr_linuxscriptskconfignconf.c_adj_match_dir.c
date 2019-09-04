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
typedef  scalar_t__ match_f ;

/* Variables and functions */
 scalar_t__ FIND_NEXT_MATCH_DOWN ; 
 scalar_t__ FIND_NEXT_MATCH_UP ; 
 scalar_t__ MATCH_TINKER_PATTERN_DOWN ; 
 scalar_t__ MATCH_TINKER_PATTERN_UP ; 

__attribute__((used)) static void adj_match_dir(match_f *match_direction)
{
	if (*match_direction == FIND_NEXT_MATCH_DOWN)
		*match_direction =
			MATCH_TINKER_PATTERN_DOWN;
	else if (*match_direction == FIND_NEXT_MATCH_UP)
		*match_direction =
			MATCH_TINKER_PATTERN_UP;
	/* else, do no change.. */
}