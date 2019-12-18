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
typedef  int uint32 ;

/* Variables and functions */
#define  PG_WAIT_ACTIVITY 136 
#define  PG_WAIT_BUFFER_PIN 135 
#define  PG_WAIT_CLIENT 134 
#define  PG_WAIT_EXTENSION 133 
#define  PG_WAIT_IO 132 
#define  PG_WAIT_IPC 131 
#define  PG_WAIT_LOCK 130 
#define  PG_WAIT_LWLOCK 129 
#define  PG_WAIT_TIMEOUT 128 

const char *
pgstat_get_wait_event_type(uint32 wait_event_info)
{
	uint32		classId;
	const char *event_type;

	/* report process as not waiting. */
	if (wait_event_info == 0)
		return NULL;

	classId = wait_event_info & 0xFF000000;

	switch (classId)
	{
		case PG_WAIT_LWLOCK:
			event_type = "LWLock";
			break;
		case PG_WAIT_LOCK:
			event_type = "Lock";
			break;
		case PG_WAIT_BUFFER_PIN:
			event_type = "BufferPin";
			break;
		case PG_WAIT_ACTIVITY:
			event_type = "Activity";
			break;
		case PG_WAIT_CLIENT:
			event_type = "Client";
			break;
		case PG_WAIT_EXTENSION:
			event_type = "Extension";
			break;
		case PG_WAIT_IPC:
			event_type = "IPC";
			break;
		case PG_WAIT_TIMEOUT:
			event_type = "Timeout";
			break;
		case PG_WAIT_IO:
			event_type = "IO";
			break;
		default:
			event_type = "???";
			break;
	}

	return event_type;
}