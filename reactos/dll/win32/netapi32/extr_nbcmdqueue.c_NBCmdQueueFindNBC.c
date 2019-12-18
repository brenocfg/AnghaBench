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
struct NBCmdQueue {scalar_t__ head; } ;
typedef  scalar_t__ PNCB ;

/* Variables and functions */
 scalar_t__* NEXT_PTR (scalar_t__) ; 

__attribute__((used)) static PNCB *NBCmdQueueFindNBC(struct NBCmdQueue *queue, PNCB ncb)
{
    PNCB *ret;

    if (!queue || !ncb)
        ret = NULL;
    else
    {
        ret = &queue->head;
        while (ret && *ret != ncb)
            ret = NEXT_PTR(*ret);
    }
    return ret;
}