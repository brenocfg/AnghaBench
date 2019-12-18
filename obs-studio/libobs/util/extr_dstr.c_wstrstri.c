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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 size_t wcslen (int /*<<< orphan*/  const*) ; 
 scalar_t__ wstrcmpi_n (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

wchar_t *wstrstri(const wchar_t *str, const wchar_t *find)
{
	size_t len;

	if (!str || !find)
		return NULL;

	len = wcslen(find);

	do {
		if (wstrcmpi_n(str, find, len) == 0)
			return (wchar_t *)str;
	} while (*str++);

	return NULL;
}