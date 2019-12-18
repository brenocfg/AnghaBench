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
struct match_state {TYPE_1__* capture; } ;
struct TYPE_2__ {char const* len; int init; } ;

/* Variables and functions */
 char const* CAP_UNFINISHED ; 
 int capture_to_close (struct match_state*) ; 
 char* match (struct match_state*,char const*,char const*) ; 

__attribute__((used)) static const char *
end_capture(struct match_state *ms, const char *s, const char *p)
{
	int l = capture_to_close(ms);
	const char *res;
	if (l == -1)
		return NULL;
	/* close capture */
	ms->capture[l].len = s - ms->capture[l].init;
	/* undo capture if match failed */
	if ((res = match(ms, s, p)) == NULL)
		ms->capture[l].len = CAP_UNFINISHED;
	return res;
}