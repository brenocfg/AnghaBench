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
struct TYPE_3__ {scalar_t__ hFile; int /*<<< orphan*/  Name; int /*<<< orphan*/  Path; int /*<<< orphan*/  BaseOfDll; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__* PLIB_ITEM ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LIB_ITEM ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 size_t MAX_PATH ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int PLIB_MAX ; 
 int /*<<< orphan*/  R_LOG_ERROR (char*) ; 
 scalar_t__ VirtualAlloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ lstLib ; 
 TYPE_1__* lstLibPtr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static void __r_debug_lstLibAdd(DWORD pid, LPVOID lpBaseOfDll, HANDLE hFile, char *dllname) {
	if (lstLib == 0) {
		lstLib = VirtualAlloc (0, PLIB_MAX * sizeof (LIB_ITEM), MEM_COMMIT, PAGE_READWRITE);
	}
	lstLibPtr = (PLIB_ITEM)lstLib;
	if (!lstLibPtr) {
		R_LOG_ERROR ("Failed to allocate memory");
		return;
	}
	for (int x = 0; x < PLIB_MAX; x++) {
		if (lstLibPtr->hFile == hFile) {
			return;
		}
		if (!lstLibPtr->hFile) {
			lstLibPtr->pid = pid;
			lstLibPtr->hFile = hFile; //DBGEvent->u.LoadDll.hFile;
			lstLibPtr->BaseOfDll = lpBaseOfDll;//DBGEvent->u.LoadDll.lpBaseOfDll;
			strncpy (lstLibPtr->Path, dllname, MAX_PATH - 1);
			int i = strlen (dllname);
			int n = i;
			while (dllname[i] != '\\' && i >= 0) {
				i--;
			}
			strncpy (lstLibPtr->Name, dllname + i + 1, (size_t)n - i);
			return;
		}
		lstLibPtr++;
	}
	eprintf ("__r_debug_lstLibAdd: Cannot find slot\n");
}