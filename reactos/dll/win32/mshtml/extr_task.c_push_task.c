#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  thread_hwnd; int /*<<< orphan*/  task_list; } ;
typedef  TYPE_1__ thread_data_t ;
struct TYPE_11__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  (* destr ) (TYPE_2__*) ;int /*<<< orphan*/  (* proc ) (TYPE_2__*) ;int /*<<< orphan*/  target_magic; } ;
typedef  TYPE_2__ task_t ;
typedef  int /*<<< orphan*/  (* task_proc_t ) (TYPE_2__*) ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_PROCESSTASK ; 
 int /*<<< orphan*/  default_task_destr (TYPE_2__*) ; 
 TYPE_1__* get_thread_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT push_task(task_t *task, task_proc_t proc, task_proc_t destr, LONG magic)
{
    thread_data_t *thread_data;

    thread_data = get_thread_data(TRUE);
    if(!thread_data) {
        if(destr)
            destr(task);
        else
            heap_free(task);
        return E_OUTOFMEMORY;
    }

    task->target_magic = magic;
    task->proc = proc;
    task->destr = destr ? destr : default_task_destr;

    list_add_tail(&thread_data->task_list, &task->entry);

    PostMessageW(thread_data->thread_hwnd, WM_PROCESSTASK, 0, 0);
    return S_OK;
}