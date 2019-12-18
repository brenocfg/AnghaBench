#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  header; TYPE_4__* bsc; } ;
typedef  TYPE_3__ stop_request_task_t ;
struct TYPE_8__ {TYPE_2__* window; int /*<<< orphan*/  IBindStatusCallback_iface; int /*<<< orphan*/  readed; } ;
struct TYPE_11__ {TYPE_1__ bsc; } ;
typedef  TYPE_4__ nsChannelBSC ;
struct TYPE_9__ {int /*<<< orphan*/  task_magic; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IBindStatusCallback_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_3__* heap_alloc (int) ; 
 int /*<<< orphan*/  on_start_nsrequest (TYPE_4__*) ; 
 int /*<<< orphan*/  push_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_request_proc ; 
 int /*<<< orphan*/  stop_request_task_destr ; 

__attribute__((used)) static HRESULT async_stop_request(nsChannelBSC *This)
{
    stop_request_task_t *task;

    if(!This->bsc.readed) {
        TRACE("No data read, calling OnStartRequest\n");
        on_start_nsrequest(This);
    }

    task = heap_alloc(sizeof(*task));
    if(!task)
        return E_OUTOFMEMORY;

    IBindStatusCallback_AddRef(&This->bsc.IBindStatusCallback_iface);
    task->bsc = This;

    return push_task(&task->header, stop_request_proc, stop_request_task_destr, This->bsc.window->task_magic);
}