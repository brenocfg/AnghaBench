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
struct TYPE_4__ {size_t m_mediaChannel; size_t m_channelsAllocatedIn; int /*<<< orphan*/  m_pauseStamp; int /*<<< orphan*/ * m_channelTimestamp; } ;
typedef  TYPE_1__ RTMP ;

/* Variables and functions */
 int RTMP_SendPause (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int RTMP_Pause(RTMP *r, int DoPause)
{
    if (DoPause)
        r->m_pauseStamp = r->m_mediaChannel < r->m_channelsAllocatedIn ?
                          r->m_channelTimestamp[r->m_mediaChannel] : 0;
    return RTMP_SendPause(r, DoPause, r->m_pauseStamp);
}