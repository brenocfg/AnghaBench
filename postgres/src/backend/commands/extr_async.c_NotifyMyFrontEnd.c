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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  StringInfoData ;

/* Variables and functions */
 scalar_t__ DestRemote ; 
 int /*<<< orphan*/  FrontendProtocol ; 
 int /*<<< orphan*/  INFO ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  pq_beginmessage (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ whereToSendOutput ; 

void
NotifyMyFrontEnd(const char *channel, const char *payload, int32 srcPid)
{
	if (whereToSendOutput == DestRemote)
	{
		StringInfoData buf;

		pq_beginmessage(&buf, 'A');
		pq_sendint32(&buf, srcPid);
		pq_sendstring(&buf, channel);
		if (PG_PROTOCOL_MAJOR(FrontendProtocol) >= 3)
			pq_sendstring(&buf, payload);
		pq_endmessage(&buf);

		/*
		 * NOTE: we do not do pq_flush() here.  For a self-notify, it will
		 * happen at the end of the transaction, and for incoming notifies
		 * ProcessIncomingNotify will do it after finding all the notifies.
		 */
	}
	else
		elog(INFO, "NOTIFY for \"%s\" payload \"%s\"", channel, payload);
}