#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int queue_len; int queue_head; int queue_tail; scalar_t__ num_actions; TYPE_2__* action_map; TYPE_1__* data_queue; scalar_t__ overflow; scalar_t__ hEvent; int /*<<< orphan*/  data_format; } ;
struct TYPE_6__ {int offset; int /*<<< orphan*/  uAppData; } ;
struct TYPE_5__ {int dwOfs; int /*<<< orphan*/  uAppData; void* dwSequence; void* dwTimeStamp; void* dwData; } ;
typedef  int /*<<< orphan*/  LPDIRECTINPUTDEVICE8A ;
typedef  TYPE_3__ IDirectInputDeviceImpl ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_WINE_NOTIFY_ACTIVITY ; 
 int id_to_offset (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* impl_from_IDirectInputDevice8A (int /*<<< orphan*/ ) ; 

void queue_event(LPDIRECTINPUTDEVICE8A iface, int inst_id, DWORD data, DWORD time, DWORD seq)
{
    IDirectInputDeviceImpl *This = impl_from_IDirectInputDevice8A(iface);
    int next_pos, ofs = id_to_offset(&This->data_format, inst_id);

    /* Event is being set regardless of the queue state */
    if (This->hEvent) SetEvent(This->hEvent);

    PostMessageW(GetDesktopWindow(), WM_WINE_NOTIFY_ACTIVITY, 0, 0);

    if (!This->queue_len || This->overflow || ofs < 0) return;

    next_pos = (This->queue_head + 1) % This->queue_len;
    if (next_pos == This->queue_tail)
    {
        TRACE(" queue overflowed\n");
        This->overflow = TRUE;
        return;
    }

    TRACE(" queueing %d at offset %d (queue head %d / size %d)\n",
          data, ofs, This->queue_head, This->queue_len);

    This->data_queue[This->queue_head].dwOfs       = ofs;
    This->data_queue[This->queue_head].dwData      = data;
    This->data_queue[This->queue_head].dwTimeStamp = time;
    This->data_queue[This->queue_head].dwSequence  = seq;

    /* Set uAppData by means of action mapping */
    if (This->num_actions > 0)
    {
        int i;
        for (i=0; i < This->num_actions; i++)
        {
            if (This->action_map[i].offset == ofs)
            {
                TRACE("Offset %d mapped to uAppData %lu\n", ofs, This->action_map[i].uAppData);
                This->data_queue[This->queue_head].uAppData = This->action_map[i].uAppData;
                break;
            }
        }
    }

    This->queue_head = next_pos;
    /* Send event if asked */
}