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
struct match_state {int dummy; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 char* match (struct match_state*,char const*,char const*) ; 
 scalar_t__ singlematch (struct match_state*,char const*,char const*,char const*) ; 

__attribute__((used)) static const char *
max_expand(struct match_state *ms, const char *s, const char *p, const char *ep)
{
	ptrdiff_t i = 0;
	/* counts maximum expand for item */
	while (singlematch(ms, s + i, p, ep))
		i++;
	/* keeps trying to match with the maximum repetitions */
	while (i >= 0) {
		const char *res = match(ms, (s + i), ep + 1);
		if (res)
			return res;
		/* else didn't match; reduce 1 repetition to try again */
		i--;
	}
	return NULL;
}