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
typedef  char wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t wcslen (char*) ; 

wchar_t *wcsdepad(wchar_t *str)
{
	wchar_t *temp;
	size_t len;

	if (!str)
		return str;
	if (!*str)
		return str;

	temp = str;

	/* remove preceding spaces/tabs */
	while (*temp == ' ' || *temp == '\t')
		++temp;

	len = wcslen(str);
	if (temp != str)
		memmove(str, temp, (len + 1) * sizeof(wchar_t));

	if (len) {
		temp = str + (len - 1);
		while (*temp == ' ' || *temp == '\t')
			*(temp--) = 0;
	}

	return str;
}