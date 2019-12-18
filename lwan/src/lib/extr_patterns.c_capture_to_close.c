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
struct match_state {int level; TYPE_1__* capture; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ CAP_UNFINISHED ; 
 int match_error (struct match_state*,char*) ; 

__attribute__((used)) static int
capture_to_close(struct match_state *ms)
{
	int level = ms->level;
	for (level--; level >= 0; level--)
		if (ms->capture[level].len == CAP_UNFINISHED)
			return (level);
	return match_error(ms, "invalid pattern capture");
}