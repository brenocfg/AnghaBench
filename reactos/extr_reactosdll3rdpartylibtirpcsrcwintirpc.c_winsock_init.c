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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  WSAData ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ init ; 
 int /*<<< orphan*/  tirpc_report (char*) ; 

BOOL winsock_init(void)
{
	int err;
	err = WSAStartup(MAKEWORD( 3, 3 ), &WSAData);	// XXX THIS SHOULD BE FAILING!!!!!!!!!!!!!!!!!
	if (err != 0) {
		init = 0;
		tirpc_report(L"WSAStartup failed!\n");
		WSACleanup();
		return FALSE;
	}
	return TRUE;
}