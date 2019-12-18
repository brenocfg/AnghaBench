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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_3__ {int /*<<< orphan*/ * type; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PKULL_M_HANDLE_ENUM_CALLBACK ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  TYPE_1__ HANDLE_ENUM_DATA ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_handle_getHandles (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kull_m_handle_getHandlesOfType_callback ; 

NTSTATUS kull_m_handle_getHandlesOfType(PKULL_M_HANDLE_ENUM_CALLBACK callBack, LPCTSTR type, DWORD dwDesiredAccess, DWORD dwOptions, PVOID pvArg)
{
	UNICODE_STRING uStr;
	HANDLE_ENUM_DATA data = {NULL, dwDesiredAccess, dwOptions, callBack, pvArg};
	if(type)
	{
		RtlInitUnicodeString(&uStr, type);
		data.type = &uStr;
	}
	return kull_m_handle_getHandles(kull_m_handle_getHandlesOfType_callback, &data);
}