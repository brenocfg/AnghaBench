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
struct TYPE_3__ {scalar_t__* m_body; int /*<<< orphan*/  m_nBodySize; int /*<<< orphan*/  m_nInfoField2; int /*<<< orphan*/  m_nTimeStamp; int /*<<< orphan*/  m_nChannel; int /*<<< orphan*/  m_packetType; } ;
typedef  TYPE_1__ RTMPPacket ;

/* Variables and functions */
 int /*<<< orphan*/  RTMP_LOGDEBUG ; 
 int /*<<< orphan*/  RTMP_Log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

void
RTMPPacket_Dump(RTMPPacket *p)
{
    RTMP_Log(RTMP_LOGDEBUG,
             "RTMP PACKET: packet type: 0x%02x. channel: 0x%02x. info 1: %d info 2: %d. Body size: %u. body: 0x%02x",
             p->m_packetType, p->m_nChannel, p->m_nTimeStamp, p->m_nInfoField2,
             p->m_nBodySize, p->m_body ? (unsigned char)p->m_body[0] : 0);
}