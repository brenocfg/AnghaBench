#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ thread_hwnd; } ;
typedef  TYPE_1__ thread_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* get_thread_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static void thread_detach(void)
{
    thread_data_t *thread_data;

    thread_data = get_thread_data(FALSE);
    if(!thread_data)
        return;

    if(thread_data->thread_hwnd)
        DestroyWindow(thread_data->thread_hwnd);

    heap_free(thread_data);
}