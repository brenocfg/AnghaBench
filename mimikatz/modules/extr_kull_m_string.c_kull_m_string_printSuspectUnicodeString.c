#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_4__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Buffer; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,TYPE_1__*) ; 
 scalar_t__ kull_m_string_suspectUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void kull_m_string_printSuspectUnicodeString(PVOID data, DWORD size)
{
	UNICODE_STRING uString = {(USHORT) size, (USHORT) size, (LPWSTR) data};
	if(kull_m_string_suspectUnicodeString(&uString))
		kprintf(L"%wZ", &uString);
	else 
		kull_m_string_wprintf_hex(uString.Buffer, uString.Length, 1);
}