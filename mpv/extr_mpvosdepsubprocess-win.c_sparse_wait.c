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
typedef  scalar_t__ HANDLE ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INFINITE ; 
 unsigned int MP_ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 unsigned int WaitForMultipleObjects (unsigned int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sparse_wait(HANDLE *handles, unsigned num_handles)
{
    unsigned w_num_handles = 0;
    HANDLE w_handles[10];
    int map[10];
    if (num_handles > MP_ARRAY_SIZE(w_handles))
        return -1;

    for (unsigned i = 0; i < num_handles; i++) {
        if (!handles[i])
            continue;

        w_handles[w_num_handles] = handles[i];
        map[w_num_handles] = i;
        w_num_handles++;
    }

    if (w_num_handles == 0)
        return -1;
    DWORD i = WaitForMultipleObjects(w_num_handles, w_handles, FALSE, INFINITE);
    i -= WAIT_OBJECT_0;

    if (i >= w_num_handles)
        return -1;
    return map[i];
}