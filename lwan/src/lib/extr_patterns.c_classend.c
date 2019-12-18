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
struct match_state {char const* p_end; } ;

/* Variables and functions */
#define  L_ESC 128 
 int /*<<< orphan*/  match_error (struct match_state*,char*) ; 

__attribute__((used)) static const char *
classend(struct match_state *ms, const char *p)
{
	switch (*p++) {
	case L_ESC:
		if (p == ms->p_end)
			match_error(ms,
			    "malformed pattern (ends with '%')");
		return p + 1;
	case '[':
		if (*p == '^')
			p++;
		do {
			/* look for a ']' */
			if (p == ms->p_end) {
				match_error(ms,
				    "malformed pattern (missing ']')");
				break;
			}
			if (*(p++) == L_ESC && p < ms->p_end) {
				/* skip escapes (e.g. '%]') */
				p++;
			}
		} while (*p != ']');
		return p + 1;
	default:
		return p;
	}
}