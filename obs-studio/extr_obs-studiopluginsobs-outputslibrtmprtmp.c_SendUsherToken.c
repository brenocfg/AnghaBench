#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pbuf ;
struct TYPE_12__ {int /*<<< orphan*/  av_val; } ;
struct TYPE_11__ {int /*<<< orphan*/  m_numInvokes; } ;
struct TYPE_10__ {int m_nChannel; char* m_body; int m_nBodySize; scalar_t__ m_hasAbsTimestamp; scalar_t__ m_nInfoField2; scalar_t__ m_nTimeStamp; int /*<<< orphan*/  m_packetType; int /*<<< orphan*/  m_headerType; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  TYPE_2__ RTMP ;
typedef  TYPE_3__ AVal ;

/* Variables and functions */
 char* AMF_EncodeNumber (char*,char*,int /*<<< orphan*/ ) ; 
 char* AMF_EncodeString (char*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  AMF_NULL ; 
 int FALSE ; 
 int /*<<< orphan*/  RTMP_LOGDEBUG ; 
 int /*<<< orphan*/  RTMP_Log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int RTMP_MAX_HEADER_SIZE ; 
 int /*<<< orphan*/  RTMP_PACKET_SIZE_MEDIUM ; 
 int /*<<< orphan*/  RTMP_PACKET_TYPE_INVOKE ; 
 int RTMP_SendPacket (TYPE_2__*,TYPE_1__*,int) ; 
 TYPE_3__ av_NetStream_Authenticate_UsherToken ; 

__attribute__((used)) static int
SendUsherToken(RTMP *r, AVal *usherToken)
{
    RTMPPacket packet;
    char pbuf[1024], *pend = pbuf + sizeof(pbuf);
    char *enc;
    packet.m_nChannel = 0x03;	/* control channel (invoke) */
    packet.m_headerType = RTMP_PACKET_SIZE_MEDIUM;
    packet.m_packetType = RTMP_PACKET_TYPE_INVOKE;
    packet.m_nTimeStamp = 0;
    packet.m_nInfoField2 = 0;
    packet.m_hasAbsTimestamp = 0;
    packet.m_body = pbuf + RTMP_MAX_HEADER_SIZE;

    RTMP_Log(RTMP_LOGDEBUG, "UsherToken: %s", usherToken->av_val);
    enc = packet.m_body;
    enc = AMF_EncodeString(enc, pend, &av_NetStream_Authenticate_UsherToken);
    enc = AMF_EncodeNumber(enc, pend, ++r->m_numInvokes);
    *enc++ = AMF_NULL;
    enc = AMF_EncodeString(enc, pend, usherToken);

    if (!enc)
        return FALSE;

    packet.m_nBodySize = enc - packet.m_body;

    return RTMP_SendPacket(r, &packet, FALSE);
}