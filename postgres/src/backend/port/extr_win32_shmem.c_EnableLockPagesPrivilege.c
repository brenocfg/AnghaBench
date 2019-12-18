#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int PrivilegeCount; TYPE_1__* Privileges; } ;
struct TYPE_4__ {int /*<<< orphan*/  Attributes; int /*<<< orphan*/  Luid; } ;
typedef  TYPE_2__ TOKEN_PRIVILEGES ;
typedef  int /*<<< orphan*/  LUID ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustTokenPrivileges (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 scalar_t__ ERROR_NOT_ALL_ASSIGNED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LookupPrivilegeValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenProcessToken (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SE_LOCK_MEMORY_NAME ; 
 int /*<<< orphan*/  SE_PRIVILEGE_ENABLED ; 
 int TOKEN_ADJUST_PRIVILEGES ; 
 int TOKEN_QUERY ; 
 int TRUE ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 

__attribute__((used)) static bool
EnableLockPagesPrivilege(int elevel)
{
	HANDLE		hToken;
	TOKEN_PRIVILEGES tp;
	LUID		luid;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		ereport(elevel,
				(errmsg("could not enable Lock Pages in Memory user right: error code %lu", GetLastError()),
				 errdetail("Failed system call was %s.", "OpenProcessToken")));
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL, SE_LOCK_MEMORY_NAME, &luid))
	{
		ereport(elevel,
				(errmsg("could not enable Lock Pages in Memory user right: error code %lu", GetLastError()),
				 errdetail("Failed system call was %s.", "LookupPrivilegeValue")));
		CloseHandle(hToken);
		return FALSE;
	}
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL))
	{
		ereport(elevel,
				(errmsg("could not enable Lock Pages in Memory user right: error code %lu", GetLastError()),
				 errdetail("Failed system call was %s.", "AdjustTokenPrivileges")));
		CloseHandle(hToken);
		return FALSE;
	}

	if (GetLastError() != ERROR_SUCCESS)
	{
		if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
			ereport(elevel,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("could not enable Lock Pages in Memory user right"),
					 errhint("Assign Lock Pages in Memory user right to the Windows user account which runs PostgreSQL.")));
		else
			ereport(elevel,
					(errmsg("could not enable Lock Pages in Memory user right: error code %lu", GetLastError()),
					 errdetail("Failed system call was %s.", "AdjustTokenPrivileges")));
		CloseHandle(hToken);
		return FALSE;
	}

	CloseHandle(hToken);

	return TRUE;
}