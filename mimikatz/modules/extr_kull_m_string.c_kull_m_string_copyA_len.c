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
typedef  scalar_t__ LPSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL kull_m_string_copyA_len(LPSTR *dst, LPCSTR src, size_t size)
{
	BOOL status = FALSE;
	if(src && dst && size)
	{
		size = (size + 1) * sizeof(char);
		if(*dst = (LPSTR) LocalAlloc(LPTR, size))
		{
			RtlCopyMemory(*dst, src, size);
			status = TRUE;
		}
	}
	return status;
}