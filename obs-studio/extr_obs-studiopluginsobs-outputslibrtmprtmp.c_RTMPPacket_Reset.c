#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ m_nBytesRead; scalar_t__ m_nBodySize; int /*<<< orphan*/  m_hasAbsTimestamp; scalar_t__ m_nInfoField2; scalar_t__ m_nTimeStamp; scalar_t__ m_nChannel; scalar_t__ m_packetType; scalar_t__ m_headerType; } ;
typedef  TYPE_1__ RTMPPacket ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

void
RTMPPacket_Reset(RTMPPacket *p)
{
    p->m_headerType = 0;
    p->m_packetType = 0;
    p->m_nChannel = 0;
    p->m_nTimeStamp = 0;
    p->m_nInfoField2 = 0;
    p->m_hasAbsTimestamp = FALSE;
    p->m_nBodySize = 0;
    p->m_nBytesRead = 0;
}