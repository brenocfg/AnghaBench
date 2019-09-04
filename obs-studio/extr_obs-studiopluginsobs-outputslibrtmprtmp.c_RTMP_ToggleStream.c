#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ status; } ;
struct TYPE_7__ {int m_pausing; int /*<<< orphan*/  m_pauseStamp; TYPE_1__ m_read; } ;
typedef  TYPE_2__ RTMP ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ RTMP_IsTimedout (TYPE_2__*) ; 
 scalar_t__ RTMP_READ_EOF ; 
 int RTMP_SendPause (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sleep (int) ; 

int
RTMP_ToggleStream(RTMP *r)
{
    int res;

    if (!r->m_pausing)
    {
        if (RTMP_IsTimedout(r) && r->m_read.status == RTMP_READ_EOF)
            r->m_read.status = 0;

        res = RTMP_SendPause(r, TRUE, r->m_pauseStamp);
        if (!res)
            return res;

        r->m_pausing = 1;
        sleep(1);
    }
    res = RTMP_SendPause(r, FALSE, r->m_pauseStamp);
    r->m_pausing = 3;
    return res;
}