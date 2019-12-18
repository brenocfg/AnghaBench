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

/* Variables and functions */
 char* match (struct match_state*,char const*,char const*) ; 
 scalar_t__ singlematch (struct match_state*,char const*,char const*,char const*) ; 

__attribute__((used)) static const char *
min_expand(struct match_state *ms, const char *s, const char *p, const char *ep)
{
	for (;;) {
		const char *res = match(ms, s, ep + 1);
		if (res != NULL)
			return res;
		else if (singlematch(ms, s, p, ep))
			s++;	/* try with one more repetition */
		else
			return NULL;
	}
}