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
UniStrncat(wchar_t *ucs1, const wchar_t *ucs2, size_t n)
{
	wchar_t *anchor = ucs1;	/* save pointer to string 1 */

	while (*ucs1++) ;
	ucs1--;			/* point to null terminator of s1 */
	while (n-- && (*ucs1 = *ucs2)) {	/* copy s2 after s1 */
		ucs1++;
		ucs2++;
	}
	*ucs1 = 0;		/* Null terminate the result */
	return (anchor);
}