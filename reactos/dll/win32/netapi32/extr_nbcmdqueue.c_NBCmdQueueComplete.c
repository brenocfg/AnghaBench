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
struct NBCmdQueue {int /*<<< orphan*/  cs; } ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PNCB ;

/* Variables and functions */
 scalar_t__* CANCEL_EVENT_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NBCmdQueueFindNBC (struct NBCmdQueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NEXT_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NRC_BADDR ; 
 int /*<<< orphan*/  NRC_GOODRET ; 
 int /*<<< orphan*/  NRC_INVADDRESS ; 
 int /*<<< orphan*/  SetEvent (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,struct NBCmdQueue*,...) ; 

UCHAR NBCmdQueueComplete(struct NBCmdQueue *queue, PNCB ncb, UCHAR retcode)
{
    UCHAR ret;
    PNCB *spot;

    TRACE(": queue %p, ncb %p\n", queue, ncb);

    if (!queue)
        return NRC_BADDR;
    if (!ncb)
        return NRC_INVADDRESS;

    EnterCriticalSection(&queue->cs);
    spot = NBCmdQueueFindNBC(queue, ncb);
    if (spot)
    {
        if (*CANCEL_EVENT_PTR(*spot))
            SetEvent(*CANCEL_EVENT_PTR(*spot));
        else
            *spot = *NEXT_PTR(*spot);
        ret = NRC_GOODRET;
    }
    else
        ret = NRC_INVADDRESS;
    LeaveCriticalSection(&queue->cs);
    TRACE("returning 0x%02x\n", ret);
    return ret;
}