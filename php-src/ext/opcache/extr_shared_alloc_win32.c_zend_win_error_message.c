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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEL_EVENT_SOURCE ; 
 int /*<<< orphan*/  DeregisterEventSource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTLOG_ERROR_TYPE ; 
 int /*<<< orphan*/  RegisterEventSource (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_win32_error_msg_free (char*) ; 
 char* php_win32_error_to_msg (int) ; 
 int /*<<< orphan*/  zend_accel_error (int,char*,char*) ; 

__attribute__((used)) static void zend_win_error_message(int type, char *msg, int err)
{
	HANDLE h;
	char *ev_msgs[2];
	char *buf = php_win32_error_to_msg(err);

	h = RegisterEventSource(NULL, TEXT(ACCEL_EVENT_SOURCE));
	ev_msgs[0] = msg;
	ev_msgs[1] = buf;
	ReportEvent(h,				  // event log handle
            EVENTLOG_ERROR_TYPE,  // event type
            0,                    // category zero
            err,				  // event identifier
            NULL,                 // no user security identifier
            2,                    // one substitution string
            0,                    // no data
            ev_msgs,              // pointer to string array
            NULL);                // pointer to data
	DeregisterEventSource(h);

	zend_accel_error(type, "%s", msg);

	php_win32_error_msg_free(buf);
}