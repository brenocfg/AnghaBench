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
typedef  scalar_t__ USHORT ;
struct TYPE_3__ {int /*<<< orphan*/  Name; scalar_t__ NameLength; int /*<<< orphan*/  ClientId; } ;
typedef  TYPE_1__* PPAC_CLIENT_INFO ;
typedef  int /*<<< orphan*/ * PFILETIME ;
typedef  int /*<<< orphan*/  PAC_CLIENT_INFO ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int lstrlen (int /*<<< orphan*/ ) ; 

BOOL kuhl_m_pac_validationInfo_to_CNAME_TINFO(PFILETIME authtime, LPCWSTR clientname, PPAC_CLIENT_INFO * pacClientInfo, DWORD * pacClientInfoLength)
{
	BOOL status = FALSE;
	DWORD len = lstrlen(clientname) * sizeof(wchar_t);

	*pacClientInfoLength = sizeof(PAC_CLIENT_INFO) + len - sizeof(wchar_t);
	if(*pacClientInfo = (PPAC_CLIENT_INFO) LocalAlloc(LPTR, *pacClientInfoLength))
	{
		(*pacClientInfo)->ClientId = *authtime;
		(*pacClientInfo)->NameLength = (USHORT) len;
		RtlCopyMemory((*pacClientInfo)->Name, clientname, len);
		status = TRUE;
	}
	return status;
}