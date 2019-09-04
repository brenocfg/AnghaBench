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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */

__attribute__((used)) static inline wchar_t *
UniStrstr(const wchar_t *ucs1, const wchar_t *ucs2)
{
	const wchar_t *anchor1 = ucs1;
	const wchar_t *anchor2 = ucs2;

	while (*ucs1) {
		if (*ucs1 == *ucs2) {
			/* Partial match found */
			ucs1++;
			ucs2++;
		} else {
			if (!*ucs2)	/* Match found */
				return (wchar_t *) anchor1;
			ucs1 = ++anchor1;	/* No match */
			ucs2 = anchor2;
		}
	}

	if (!*ucs2)		/* Both end together */
		return (wchar_t *) anchor1;	/* Match found */
	return NULL;		/* No match */
}