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

/* Variables and functions */
 int /*<<< orphan*/  COMMERROR ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ProcessStandbyHSFeedbackMessage () ; 
 int /*<<< orphan*/  ProcessStandbyReplyMessage () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char) ; 
 char pq_getmsgbyte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_message ; 

__attribute__((used)) static void
ProcessStandbyMessage(void)
{
	char		msgtype;

	/*
	 * Check message type from the first byte.
	 */
	msgtype = pq_getmsgbyte(&reply_message);

	switch (msgtype)
	{
		case 'r':
			ProcessStandbyReplyMessage();
			break;

		case 'h':
			ProcessStandbyHSFeedbackMessage();
			break;

		default:
			ereport(COMMERROR,
					(errcode(ERRCODE_PROTOCOL_VIOLATION),
					 errmsg("unexpected message type \"%c\"", msgtype)));
			proc_exit(0);
	}
}