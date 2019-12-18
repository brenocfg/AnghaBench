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
struct TYPE_7__ {int m_nBWCheckCounter; } ;
struct TYPE_6__ {int m_nChannel; int m_nTimeStamp; char* m_body; int m_nBodySize; scalar_t__ m_hasAbsTimestamp; scalar_t__ m_nInfoField2; int /*<<< orphan*/  m_packetType; int /*<<< orphan*/  m_headerType; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  TYPE_2__ RTMP ;

/* Variables and functions */
 char* AMF_EncodeNumber (char*,char*,double) ; 
 char* AMF_EncodeString (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AMF_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int RTMP_MAX_HEADER_SIZE ; 
 int /*<<< orphan*/  RTMP_PACKET_SIZE_MEDIUM ; 
 int /*<<< orphan*/  RTMP_PACKET_TYPE_INVOKE ; 
 int RTMP_SendPacket (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av__result ; 

__attribute__((used)) static int
SendCheckBWResult(RTMP *r, double txn)
{
    RTMPPacket packet;
    char pbuf[256], *pend = pbuf + sizeof(pbuf);
    char *enc;

    packet.m_nChannel = 0x03;	/* control channel (invoke) */
    packet.m_headerType = RTMP_PACKET_SIZE_MEDIUM;
    packet.m_packetType = RTMP_PACKET_TYPE_INVOKE;
    packet.m_nTimeStamp = 0x16 * r->m_nBWCheckCounter;	/* temp inc value. till we figure it out. */
    packet.m_nInfoField2 = 0;
    packet.m_hasAbsTimestamp = 0;
    packet.m_body = pbuf + RTMP_MAX_HEADER_SIZE;

    enc = packet.m_body;
    enc = AMF_EncodeString(enc, pend, &av__result);
    enc = AMF_EncodeNumber(enc, pend, txn);
    *enc++ = AMF_NULL;
    enc = AMF_EncodeNumber(enc, pend, (double)r->m_nBWCheckCounter++);

    packet.m_nBodySize = enc - packet.m_body;

    return RTMP_SendPacket(r, &packet, FALSE);
}