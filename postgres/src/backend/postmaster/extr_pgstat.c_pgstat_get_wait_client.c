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
typedef  int WaitEventClient ;

/* Variables and functions */
#define  WAIT_EVENT_CLIENT_READ 136 
#define  WAIT_EVENT_CLIENT_WRITE 135 
#define  WAIT_EVENT_GSS_OPEN_SERVER 134 
#define  WAIT_EVENT_LIBPQWALRECEIVER_CONNECT 133 
#define  WAIT_EVENT_LIBPQWALRECEIVER_RECEIVE 132 
#define  WAIT_EVENT_SSL_OPEN_SERVER 131 
#define  WAIT_EVENT_WAL_RECEIVER_WAIT_START 130 
#define  WAIT_EVENT_WAL_SENDER_WAIT_WAL 129 
#define  WAIT_EVENT_WAL_SENDER_WRITE_DATA 128 

__attribute__((used)) static const char *
pgstat_get_wait_client(WaitEventClient w)
{
	const char *event_name = "unknown wait event";

	switch (w)
	{
		case WAIT_EVENT_CLIENT_READ:
			event_name = "ClientRead";
			break;
		case WAIT_EVENT_CLIENT_WRITE:
			event_name = "ClientWrite";
			break;
		case WAIT_EVENT_LIBPQWALRECEIVER_CONNECT:
			event_name = "LibPQWalReceiverConnect";
			break;
		case WAIT_EVENT_LIBPQWALRECEIVER_RECEIVE:
			event_name = "LibPQWalReceiverReceive";
			break;
		case WAIT_EVENT_SSL_OPEN_SERVER:
			event_name = "SSLOpenServer";
			break;
		case WAIT_EVENT_WAL_RECEIVER_WAIT_START:
			event_name = "WalReceiverWaitStart";
			break;
		case WAIT_EVENT_WAL_SENDER_WAIT_WAL:
			event_name = "WalSenderWaitForWAL";
			break;
		case WAIT_EVENT_WAL_SENDER_WRITE_DATA:
			event_name = "WalSenderWriteData";
			break;
		case WAIT_EVENT_GSS_OPEN_SERVER:
			event_name = "GSSOpenServer";
			break;
			/* no default case, so that compiler will warn */
	}

	return event_name;
}