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
 char* bmalloc (size_t) ; 
 size_t os_wcs_to_mbs (int /*<<< orphan*/  const*,size_t,char*,size_t) ; 

size_t os_wcs_to_mbs_ptr(const wchar_t *str, size_t len, char **pstr)
{
	if (str) {
		size_t out_len = os_wcs_to_mbs(str, len, NULL, 0);

		*pstr = bmalloc((out_len + 1) * sizeof(char));
		return os_wcs_to_mbs(str, len, *pstr, out_len + 1);
	} else {
		*pstr = NULL;
		return 0;
	}
}