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
typedef  int /*<<< orphan*/  SCHEMA_PREFIX_TABLE ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  scalar_t__ PVOID ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  ATTRBLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,char*,int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ kull_m_rpc_drsr_findMonoAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int*) ; 

void kull_m_rpc_drsr_findPrintMonoAttr(LPCWSTR prefix, SCHEMA_PREFIX_TABLE *prefixTable, ATTRBLOCK *attributes, LPCSTR szOid, BOOL newLine)
{
	PVOID ptr;
	DWORD sz;
	if(kull_m_rpc_drsr_findMonoAttr(prefixTable, attributes, szOid, &ptr, &sz))
		kprintf(L"%s%.*s%s", prefix ? prefix : L"", sz / sizeof(wchar_t), (PWSTR) ptr, newLine ? L"\n" : L"");
}