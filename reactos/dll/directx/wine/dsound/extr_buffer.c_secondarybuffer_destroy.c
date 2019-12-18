#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dwFlags; } ;
struct TYPE_10__ {TYPE_1__ drvdesc; } ;
struct TYPE_9__ {scalar_t__ ref; struct TYPE_9__* pwfx; struct TYPE_9__* notifies; struct TYPE_9__* tmp_buffer; struct TYPE_9__* buffer; struct TYPE_9__* memory; int /*<<< orphan*/  entry; TYPE_6__* device; scalar_t__ hwbuf; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ IDirectSoundBufferImpl ;

/* Variables and functions */
 int DSDDESC_USESYSTEMMEMORY ; 
 int /*<<< orphan*/  DirectSoundDevice_RemoveBuffer (TYPE_6__*,TYPE_2__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IDsDriverBuffer_Release (scalar_t__) ; 
 int /*<<< orphan*/  RtlDeleteResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

void secondarybuffer_destroy(IDirectSoundBufferImpl *This)
{
    DirectSoundDevice_RemoveBuffer(This->device, This);
    RtlDeleteResource(&This->lock);

    if (This->hwbuf)
        IDsDriverBuffer_Release(This->hwbuf);
    if (!This->hwbuf || (This->device->drvdesc.dwFlags & DSDDESC_USESYSTEMMEMORY)) {
        This->buffer->ref--;
        list_remove(&This->entry);
        if (This->buffer->ref == 0) {
            HeapFree(GetProcessHeap(), 0, This->buffer->memory);
            HeapFree(GetProcessHeap(), 0, This->buffer);
        }
    }

    HeapFree(GetProcessHeap(), 0, This->tmp_buffer);
    HeapFree(GetProcessHeap(), 0, This->notifies);
    HeapFree(GetProcessHeap(), 0, This->pwfx);
    HeapFree(GetProcessHeap(), 0, This);

    TRACE("(%p) released\n", This);
}