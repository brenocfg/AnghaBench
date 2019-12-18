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
struct match_state {char const* src_end; } ;

/* Variables and functions */
#define  L_ESC 128 
 int match_class (int,int) ; 
 int matchbracketclass (int,char const*,char const*) ; 
 int uchar (char const) ; 

__attribute__((used)) static int
singlematch(struct match_state *ms, const char *s, const char *p,
    const char *ep)
{
	if (s >= ms->src_end)
		return 0;
	else {
		int c = uchar(*s);
		switch (*p) {
		case '.':
			/* matches any char */
			return (1);
		case L_ESC:
			return match_class(c, uchar(*(p + 1)));
		case '[':
			return matchbracketclass(c, p, ep - 1);
		default:
			return (uchar(*p) == c);
		}
	}
}