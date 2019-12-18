#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ output_message ; 
 int /*<<< orphan*/  pq_putmessage_noblock (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendbyte (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pq_sendint64 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  sentPtr ; 

__attribute__((used)) static void
WalSndKeepalive(bool requestReply)
{
	elog(DEBUG2, "sending replication keepalive");

	/* construct the message... */
	resetStringInfo(&output_message);
	pq_sendbyte(&output_message, 'k');
	pq_sendint64(&output_message, sentPtr);
	pq_sendint64(&output_message, GetCurrentTimestamp());
	pq_sendbyte(&output_message, requestReply ? 1 : 0);

	/* ... and send it wrapped in CopyData */
	pq_putmessage_noblock('d', output_message.data, output_message.len);
}