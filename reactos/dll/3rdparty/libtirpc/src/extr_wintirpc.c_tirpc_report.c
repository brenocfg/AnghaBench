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
typedef  int /*<<< orphan*/  chMsg ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ LPTSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DeregisterEventSource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVENTLOG_WARNING_TYPE ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * RegisterEventSource (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  swprintf_s (int /*<<< orphan*/ *,int,char*,int) ; 

VOID
tirpc_report(LPTSTR lpszMsg)
{
	WCHAR    chMsg[256];
	HANDLE   hEventSource;
	LPCWSTR  lpszStrings[2];

	// Use event logging to log the error.
	//
	hEventSource = RegisterEventSource(NULL,
									   TEXT("tirpc.dll"));

#ifndef __REACTOS__
	swprintf_s(chMsg, sizeof(chMsg), L"tirpc report: %d", GetLastError());
#else
	_snwprintf(chMsg, sizeof(chMsg) / sizeof(WCHAR), L"tirpc report: %d", GetLastError());
#endif
	lpszStrings[0] = (LPCWSTR)chMsg;
	lpszStrings[1] = lpszMsg;

	if (hEventSource != NULL) {
		ReportEvent(hEventSource, // handle of event source
			EVENTLOG_WARNING_TYPE, // event type
			0,                    // event category
			0,                    // event ID
			NULL,                 // current user's SID
			2,                    // strings in lpszStrings
			0,                    // no bytes of raw data
			lpszStrings,          // array of error strings
			NULL);                // no raw data

		(VOID) DeregisterEventSource(hEventSource);
	}
}