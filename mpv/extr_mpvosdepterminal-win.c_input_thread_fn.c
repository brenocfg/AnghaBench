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
typedef  void* HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForMultipleObjects (int,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* death ; 
 int /*<<< orphan*/  mpthread_set_name (char*) ; 
 int /*<<< orphan*/  read_input (void*) ; 

__attribute__((used)) static void *input_thread_fn(void *ptr)
{
    mpthread_set_name("terminal");
    HANDLE in = ptr;
    HANDLE stuff[2] = {in, death};
    while (1) {
        DWORD r = WaitForMultipleObjects(2, stuff, FALSE, INFINITE);
        if (r != WAIT_OBJECT_0)
            break;
        read_input(in);
    }
    return NULL;
}