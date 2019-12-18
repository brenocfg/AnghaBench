#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
typedef  int /*<<< orphan*/  (* WalSndSendDataCallback ) () ;
struct TYPE_2__ {scalar_t__ flush; scalar_t__ write; } ;

/* Variables and functions */
 int /*<<< orphan*/  DestRemote ; 
 int /*<<< orphan*/  EndCommand (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* MyWalSnd ; 
 scalar_t__ WalSndCaughtUp ; 
 int /*<<< orphan*/  WalSndKeepalive (int) ; 
 scalar_t__ XLogRecPtrIsInvalid (scalar_t__) ; 
 int /*<<< orphan*/  pq_flush () ; 
 int /*<<< orphan*/  pq_is_send_pending () ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ sentPtr ; 
 int waiting_for_ping_response ; 

__attribute__((used)) static void
WalSndDone(WalSndSendDataCallback send_data)
{
	XLogRecPtr	replicatedPtr;

	/* ... let's just be real sure we're caught up ... */
	send_data();

	/*
	 * To figure out whether all WAL has successfully been replicated, check
	 * flush location if valid, write otherwise. Tools like pg_receivewal will
	 * usually (unless in synchronous mode) return an invalid flush location.
	 */
	replicatedPtr = XLogRecPtrIsInvalid(MyWalSnd->flush) ?
		MyWalSnd->write : MyWalSnd->flush;

	if (WalSndCaughtUp && sentPtr == replicatedPtr &&
		!pq_is_send_pending())
	{
		/* Inform the standby that XLOG streaming is done */
		EndCommand("COPY 0", DestRemote);
		pq_flush();

		proc_exit(0);
	}
	if (!waiting_for_ping_response)
	{
		WalSndKeepalive(true);
		waiting_for_ping_response = true;
	}
}