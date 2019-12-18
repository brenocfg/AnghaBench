#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ SessionInfo ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__* session_list ; 
 int /*<<< orphan*/  session_lock ; 

VOID
DestroySession(SessionInfo* session)
{
    HANDLE heap = GetProcessHeap();
    SessionInfo* session_node;
    SessionInfo* session_prev;

    /* TODO: More cleanup stuff */

    /* Remove from the list */

    EnterCriticalSection(&session_lock);

    session_node = session_list;
    session_prev = NULL;

    while ( session_node )
    {
        if ( session_node == session )
        {
            /* Bridge the gap for when we go */
            session_prev->next = session->next;
            break;
        }

        /* Save the previous node, fetch the next */
        session_prev = session_node;
        session_node = session_node->next;
    }

    LeaveCriticalSection(&session_lock);

    HeapFree(heap, 0, session);
}