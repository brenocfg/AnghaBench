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
typedef  int* LPWSTR ;
typedef  int* LPCWSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int*) ; 
 int /*<<< orphan*/  RtlCopyMemory (int*,int*,int) ; 
 scalar_t__ wcslen (int*) ; 
 int* wcsstr (int*,int*) ; 

BOOL kull_m_string_quickxml_simplefind(LPCWSTR xml, LPCWSTR node, LPWSTR *dst)
{
	BOOL status = FALSE;
	DWORD lenNode, lenBegin, lenEnd;
	LPWSTR begin, end, curBeg, curEnd;
	lenNode = (DWORD) wcslen(node) * sizeof(wchar_t);
	lenBegin = lenNode + 3 * sizeof(wchar_t);
	lenEnd = lenNode + 4 * sizeof(wchar_t);
	if(begin = (LPWSTR) LocalAlloc(LPTR, lenBegin))
	{
		if(end = (LPWSTR) LocalAlloc(LPTR, lenEnd))
		{
			begin[0] = end[0] = L'<';
			end[1] = L'/';
			begin[lenBegin / sizeof(wchar_t) - 2] = end[lenEnd / sizeof(wchar_t) - 2] = L'>';
			RtlCopyMemory(begin + 1, node, lenNode);
			RtlCopyMemory(end + 2, node, lenNode);
			if(curBeg = wcsstr(xml, begin))
			{
				curBeg += lenBegin / sizeof(wchar_t) - 1;
				if(curEnd = wcsstr(curBeg, end))
				{
					if(status = (curBeg <= curEnd))
					{
						lenNode = (DWORD) (curEnd - curBeg) * sizeof(wchar_t);
						if((*dst) = (LPWSTR) LocalAlloc(LPTR, lenNode + sizeof(wchar_t)))
						{
							RtlCopyMemory(*dst, curBeg, lenNode);
						}
					}
				}
			}
			LocalFree(end);
		}
		LocalFree(begin);
	}
	return status;
}