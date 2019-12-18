#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dwFlags; struct TYPE_7__* lpNext; scalar_t__ reserved; scalar_t__ dwBytesRecorded; int /*<<< orphan*/  lpData; } ;
struct TYPE_6__ {TYPE_2__* next_buffer; scalar_t__ buffer_position; TYPE_2__* wave_queue; } ;
typedef  TYPE_1__ SessionInfo ;
typedef  TYPE_2__* PWAVEHDR ;
typedef  int /*<<< orphan*/  MMRESULT ;
typedef  TYPE_2__* LPWAVEHDR ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  MMSYSERR_INVALPARAM ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  WAVERR_STILLPLAYING ; 
 int /*<<< orphan*/  WAVERR_UNPREPARED ; 
 int WHDR_DONE ; 
 int WHDR_INQUEUE ; 
 int WHDR_PREPARED ; 

MMRESULT
QueueWaveBuffer(
    SessionInfo* session_info,
    LPWAVEHDR wave_header)
{
    PWAVEHDR queue_node, previous_node;
    DPRINT("Queueing wave buffer\n");

    if ( ! wave_header )
    {
        return MMSYSERR_INVALPARAM;
    }

    if ( ! wave_header->lpData )
    {
        return MMSYSERR_INVALPARAM;
    }

    /* Headers must be prepared first */
    if ( ! ( wave_header->dwFlags & WHDR_PREPARED ) )
    {
        DPRINT("I was given a header which hasn't been prepared yet!\n");
        return WAVERR_UNPREPARED;
    }

    /* ...and they must not already be in the playing queue! */
    if ( wave_header->dwFlags & WHDR_INQUEUE )
    {
        DPRINT("I was given a header for a buffer which is already playing\n");
        return WAVERR_STILLPLAYING;
    }

    /* Initialize */
    wave_header->dwBytesRecorded = 0;

    /* Clear the DONE bit, and mark the buffer as queued */
    wave_header->dwFlags &= ~WHDR_DONE;
    wave_header->dwFlags |= WHDR_INQUEUE;

    /* Save our handle in the header */
    wave_header->reserved = (DWORD_PTR) session_info;

    /* Locate the end of the queue */
    previous_node = NULL;
    queue_node = session_info->wave_queue;

    while ( queue_node )
    {
        previous_node = queue_node;
        queue_node = queue_node->lpNext;
    }

    /* Go back a step to obtain the previous node (non-NULL) */
    queue_node = previous_node;

    /* Append our buffer here, and terminate the queue */
    queue_node->lpNext = wave_header;
    wave_header->lpNext = NULL;

    /* When no buffers are playing there's no play queue so we start one */
#if 0
    if ( ! session_info->next_buffer )
    {
        session_info->buffer_position = 0;
        session_info->next_buffer = wave_header;
    }
#endif

    /* Pass to the driver - happens automatically during playback */
//    return PerformWaveIO(session_info);
    return MMSYSERR_NOERROR;
}