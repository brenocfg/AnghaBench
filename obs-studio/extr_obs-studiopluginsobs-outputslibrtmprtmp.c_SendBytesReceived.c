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
typedef  int /*<<< orphan*/  pbuf ;
struct TYPE_7__ {int /*<<< orphan*/  m_nBytesIn; int /*<<< orphan*/  m_nBytesInSent; } ;
struct TYPE_6__ {int m_nChannel; char* m_body; int m_nBodySize; scalar_t__ m_hasAbsTimestamp; scalar_t__ m_nInfoField2; scalar_t__ m_nTimeStamp; int /*<<< orphan*/  m_packetType; int /*<<< orphan*/  m_headerType; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  TYPE_2__ RTMP ;

/* Variables and functions */
 int /*<<< orphan*/  AMF_EncodeInt32 (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int RTMP_MAX_HEADER_SIZE ; 
 int /*<<< orphan*/  RTMP_PACKET_SIZE_MEDIUM ; 
 int /*<<< orphan*/  RTMP_PACKET_TYPE_BYTES_READ_REPORT ; 
 int RTMP_SendPacket (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
SendBytesReceived(RTMP *r)
{
    RTMPPacket packet;
    char pbuf[256], *pend = pbuf + sizeof(pbuf);

    packet.m_nChannel = 0x02;	/* control channel (invoke) */
    packet.m_headerType = RTMP_PACKET_SIZE_MEDIUM;
    packet.m_packetType = RTMP_PACKET_TYPE_BYTES_READ_REPORT;
    packet.m_nTimeStamp = 0;
    packet.m_nInfoField2 = 0;
    packet.m_hasAbsTimestamp = 0;
    packet.m_body = pbuf + RTMP_MAX_HEADER_SIZE;

    packet.m_nBodySize = 4;

    AMF_EncodeInt32(packet.m_body, pend, r->m_nBytesIn);	/* hard coded for now */
    r->m_nBytesInSent = r->m_nBytesIn;

    /*RTMP_Log(RTMP_LOGDEBUG, "Send bytes report. 0x%x (%d bytes)", (unsigned int)m_nBytesIn, m_nBytesIn); */
    return RTMP_SendPacket(r, &packet, FALSE);
}