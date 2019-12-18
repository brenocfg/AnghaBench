#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int /*<<< orphan*/  DaylightName; int /*<<< orphan*/  StandardName; } ;
typedef  TYPE_1__ TIME_ZONE_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemTimeAsFileTime (int /*<<< orphan*/ *) ; 
 scalar_t__ GetTimeZoneInformation (TYPE_1__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ TIME_ZONE_ID_INVALID ; 
 scalar_t__ TIME_ZONE_ID_STANDARD ; 
 scalar_t__ TIME_ZONE_ID_UNKNOWN ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_displayFileTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_displayLocalFileTime (int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_standard_localtime(int argc, wchar_t * argv[])
{
	FILETIME ft;
	TIME_ZONE_INFORMATION tzi;
	DWORD dwTzi;
	GetSystemTimeAsFileTime(&ft);
	dwTzi = GetTimeZoneInformation(&tzi);
	kprintf(L"Local: "); kull_m_string_displayLocalFileTime(&ft); kprintf(L"\n");
	if(dwTzi != TIME_ZONE_ID_INVALID && dwTzi != TIME_ZONE_ID_UNKNOWN)
		kprintf(L"Zone : %.32s\n", (dwTzi == TIME_ZONE_ID_STANDARD) ? tzi.StandardName : tzi.DaylightName);
	kprintf(L"UTC  : "); kull_m_string_displayFileTime(&ft); kprintf(L"\n");
	return STATUS_SUCCESS;
}