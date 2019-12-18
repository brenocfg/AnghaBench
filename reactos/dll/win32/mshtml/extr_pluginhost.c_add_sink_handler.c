#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * disp; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ sink_entry_t ;
struct TYPE_10__ {int handlers_size; int handlers_cnt; TYPE_1__* handlers; } ;
typedef  TYPE_2__ PHEventSink ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 TYPE_1__* find_sink_entry (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_alloc (int) ; 
 TYPE_1__* heap_realloc (TYPE_1__*,int) ; 

__attribute__((used)) static void add_sink_handler(PHEventSink *sink, DISPID id, IDispatch *disp)
{
    sink_entry_t *entry = find_sink_entry(sink, id);

    if(entry) {
        if(entry->disp)
            IDispatch_Release(entry->disp);
    }else {
        if(!sink->handlers_size) {
            sink->handlers = heap_alloc(4*sizeof(*sink->handlers));
            if(!sink->handlers)
                return;
            sink->handlers_size = 4;
        }else if(sink->handlers_cnt == sink->handlers_size) {
            sink_entry_t *new_handlers;

            new_handlers = heap_realloc(sink->handlers, 2*sink->handlers_size*sizeof(*sink->handlers));
            if(!new_handlers)
                return;
            sink->handlers = new_handlers;
            sink->handlers_size *= 2;
        }
        entry = sink->handlers + sink->handlers_cnt++;
        entry->id = id;
    }

    IDispatch_AddRef(disp);
    entry->disp = disp;
}