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
struct aa_ns {int /*<<< orphan*/  sub_ns; } ;

/* Variables and functions */
 struct aa_ns* __aa_findn_ns (int /*<<< orphan*/ *,char const*,size_t) ; 
 char* strnstr (char const*,char*,size_t) ; 

struct aa_ns *__aa_lookupn_ns(struct aa_ns *view, const char *hname, size_t n)
{
	struct aa_ns *ns = view;
	const char *split;

	for (split = strnstr(hname, "//", n); split;
	     split = strnstr(hname, "//", n)) {
		ns = __aa_findn_ns(&ns->sub_ns, hname, split - hname);
		if (!ns)
			return NULL;

		n -= split + 2 - hname;
		hname = split + 2;
	}

	if (n)
		return __aa_findn_ns(&ns->sub_ns, hname, n);
	return NULL;
}