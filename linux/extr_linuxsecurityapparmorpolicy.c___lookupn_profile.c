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
struct aa_policy {int /*<<< orphan*/  profiles; } ;
struct aa_profile {struct aa_policy base; } ;

/* Variables and functions */
 struct aa_profile* __strn_find_child (int /*<<< orphan*/ *,char const*,size_t) ; 
 char* strnstr (char const*,char*,size_t) ; 

__attribute__((used)) static struct aa_profile *__lookupn_profile(struct aa_policy *base,
					    const char *hname, size_t n)
{
	struct aa_profile *profile = NULL;
	const char *split;

	for (split = strnstr(hname, "//", n); split;
	     split = strnstr(hname, "//", n)) {
		profile = __strn_find_child(&base->profiles, hname,
					    split - hname);
		if (!profile)
			return NULL;

		base = &profile->base;
		n -= split + 2 - hname;
		hname = split + 2;
	}

	if (n)
		return __strn_find_child(&base->profiles, hname, n);
	return NULL;
}