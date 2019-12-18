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
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL kull_m_string_copy_len(LPWSTR *dst, LPCWSTR src, size_t size)
{
	BOOL status = FALSE;
	if(src && dst && size)
	{
		size = (size + 1) * sizeof(wchar_t);
		if(*dst = (LPWSTR) LocalAlloc(LPTR, size))
		{
			RtlCopyMemory(*dst, src, size);
			status = TRUE;
		}
	}
	return status;
}