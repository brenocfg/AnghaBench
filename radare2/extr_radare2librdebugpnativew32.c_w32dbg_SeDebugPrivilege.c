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
struct TYPE_4__ {scalar_t__ Attributes; int /*<<< orphan*/  Luid; } ;
typedef  TYPE_2__ TOKEN_PRIVILEGES ;
typedef  int /*<<< orphan*/  LUID ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 scalar_t__ AdjustTokenPrivileges (int /*<<< orphan*/ *,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LookupPrivilegeValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SE_DEBUG_NAME ; 
 scalar_t__ SE_PRIVILEGE_ENABLED ; 
 int /*<<< orphan*/  TOKEN_ADJUST_PRIVILEGES ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 

__attribute__((used)) static bool w32dbg_SeDebugPrivilege() {
	/////////////////////////////////////////////////////////
	//   Note: Enabling SeDebugPrivilege adapted from sample
	//     MSDN @ http://msdn.microsoft.com/en-us/library/aa446619%28VS.85%29.aspx
	// Enable SeDebugPrivilege
	bool ret = true;
	TOKEN_PRIVILEGES tokenPriv;
	HANDLE hToken = NULL;
	LUID luidDebug;
	if (!OpenProcessToken (GetCurrentProcess (),
			TOKEN_ADJUST_PRIVILEGES, &hToken))
		return false;

	if (!LookupPrivilegeValue (NULL, SE_DEBUG_NAME, &luidDebug)) {
		CloseHandle (hToken);
		return false;
	}

	tokenPriv.PrivilegeCount = 1;
	tokenPriv.Privileges[0].Luid = luidDebug;
	tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (AdjustTokenPrivileges (hToken, FALSE, &tokenPriv, 0, NULL, NULL) != FALSE) {
		if (tokenPriv.Privileges[0].Attributes == SE_PRIVILEGE_ENABLED) {
		//	eprintf ("PRIV ENABLED\n");
		}
		// Always successful, even in the cases which lead to OpenProcess failure
		//	eprintf ("Successfully changed token privileges.\n");
		// XXX if we cant get the token nobody tells?? wtf
	} else {
		eprintf ("Failed to change token privileges 0x%x\n", (int)GetLastError());
		ret = false;
	}
	CloseHandle (hToken);
	return ret;
}