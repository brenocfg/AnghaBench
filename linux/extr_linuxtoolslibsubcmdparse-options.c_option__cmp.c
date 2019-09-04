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
struct option {scalar_t__ long_name; int /*<<< orphan*/  short_name; } ;

/* Variables and functions */
 int strcmp (char const*,char const*) ; 
 int tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int option__cmp(const void *va, const void *vb)
{
	const struct option *a = va, *b = vb;
	int sa = tolower(a->short_name), sb = tolower(b->short_name), ret;

	if (sa == 0)
		sa = 'z' + 1;
	if (sb == 0)
		sb = 'z' + 1;

	ret = sa - sb;

	if (ret == 0) {
		const char *la = a->long_name ?: "",
			   *lb = b->long_name ?: "";
		ret = strcmp(la, lb);
	}

	return ret;
}