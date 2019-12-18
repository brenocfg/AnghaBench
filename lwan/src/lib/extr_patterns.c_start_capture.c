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
struct match_state {int level; int maxcaptures; TYPE_1__* capture; } ;
struct TYPE_2__ {char const* init; int len; } ;

/* Variables and functions */
 char* match (struct match_state*,char const*,char const*) ; 
 int /*<<< orphan*/  match_error (struct match_state*,char*) ; 

__attribute__((used)) static const char *
start_capture(struct match_state *ms, const char *s, const char *p, int what)
{
	const char *res;

	int level = ms->level;
	if (level >= ms->maxcaptures) {
		match_error(ms, "too many captures");
		return (NULL);
	}
	ms->capture[level].init = s;
	ms->capture[level].len = what;
	ms->level = level + 1;
	/* undo capture if match failed */
	if ((res = match(ms, s, p)) == NULL)
		ms->level--;
	return res;
}