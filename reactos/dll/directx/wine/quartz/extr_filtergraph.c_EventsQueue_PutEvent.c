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
struct TYPE_3__ {int msg_toget; int msg_tosave; int ring_buffer_size; int /*<<< orphan*/  msg_crst; int /*<<< orphan*/  msg_event; int /*<<< orphan*/ * messages; } ;
typedef  TYPE_1__ EventsQueue ;
typedef  int /*<<< orphan*/  Event ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CoTaskMemRealloc (int /*<<< orphan*/ *,int) ; 
 size_t EVENTS_RING_BUFFER_INCREMENT ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL EventsQueue_PutEvent(EventsQueue* omr, const Event* evt)
{
    EnterCriticalSection(&omr->msg_crst);
    if (omr->msg_toget == ((omr->msg_tosave + 1) % omr->ring_buffer_size))
    {
	int old_ring_buffer_size = omr->ring_buffer_size;
	omr->ring_buffer_size += EVENTS_RING_BUFFER_INCREMENT;
	TRACE("omr->ring_buffer_size=%d\n",omr->ring_buffer_size);
	omr->messages = CoTaskMemRealloc(omr->messages, omr->ring_buffer_size * sizeof(Event));
	/* Now we need to rearrange the ring buffer so that the new
	   buffers just allocated are in between omr->msg_tosave and
	   omr->msg_toget.
	*/
	if (omr->msg_tosave < omr->msg_toget)
	{
	    memmove(&(omr->messages[omr->msg_toget + EVENTS_RING_BUFFER_INCREMENT]),
		    &(omr->messages[omr->msg_toget]),
		    sizeof(Event)*(old_ring_buffer_size - omr->msg_toget)
		    );
	    omr->msg_toget += EVENTS_RING_BUFFER_INCREMENT;
	}
    }
    omr->messages[omr->msg_tosave] = *evt;
    SetEvent(omr->msg_event);
    omr->msg_tosave = (omr->msg_tosave + 1) % omr->ring_buffer_size;
    LeaveCriticalSection(&omr->msg_crst);
    return TRUE;
}