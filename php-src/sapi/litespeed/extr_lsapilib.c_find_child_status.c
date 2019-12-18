#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int m_pid; } ;
typedef  TYPE_1__ lsapi_child_status ;
struct TYPE_5__ {TYPE_1__* m_pChildrenStatusCur; TYPE_1__* m_pChildrenStatusEnd; TYPE_1__* m_pChildrenStatus; } ;

/* Variables and functions */
 TYPE_2__* g_prefork_server ; 

__attribute__((used)) static lsapi_child_status * find_child_status( int pid )
{
    lsapi_child_status * pStatus = g_prefork_server->m_pChildrenStatus;
    lsapi_child_status * pEnd = g_prefork_server->m_pChildrenStatusEnd;
    while( pStatus < pEnd )
    {
        if ( pStatus->m_pid == pid )
        {
            if ( pStatus + 1 > g_prefork_server->m_pChildrenStatusCur )
                g_prefork_server->m_pChildrenStatusCur = pStatus + 1;
            return pStatus;
        }
        ++pStatus;
    }
    return NULL;
}