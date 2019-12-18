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
struct match_state {char const* src_end; TYPE_1__* capture; } ;
struct TYPE_2__ {int /*<<< orphan*/  init; scalar_t__ len; } ;

/* Variables and functions */
 int check_capture (struct match_state*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static const char *
match_capture(struct match_state *ms, const char *s, int l)
{
	size_t len;
	l = check_capture(ms, l);
	if (l == -1)
		return NULL;
	len = (size_t)ms->capture[l].len;
	if ((size_t) (ms->src_end - s) >= len &&
	    memcmp(ms->capture[l].init, s, len) == 0)
		return s + len;
	else
		return NULL;
}