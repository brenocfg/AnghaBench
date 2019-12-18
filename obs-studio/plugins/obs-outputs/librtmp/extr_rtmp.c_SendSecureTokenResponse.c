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
typedef  int /*<<< orphan*/  pbuf ;
struct TYPE_3__ {int m_nChannel; char* m_body; int m_nBodySize; scalar_t__ m_hasAbsTimestamp; scalar_t__ m_nInfoField2; scalar_t__ m_nTimeStamp; int /*<<< orphan*/  m_packetType; int /*<<< orphan*/  m_headerType; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  int /*<<< orphan*/  RTMP ;
typedef  int /*<<< orphan*/  AVal ;

/* Variables and functions */
 char* AMF_EncodeNumber (char*,char*,double) ; 
 char* AMF_EncodeString (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AMF_NULL ; 
 int FALSE ; 
 int RTMP_MAX_HEADER_SIZE ; 
 int /*<<< orphan*/  RTMP_PACKET_SIZE_MEDIUM ; 
 int /*<<< orphan*/  RTMP_PACKET_TYPE_INVOKE ; 
 int RTMP_SendPacket (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_secureTokenResponse ; 

__attribute__((used)) static int
SendSecureTokenResponse(RTMP *r, AVal *resp)
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

    enc = packet.m_body;
    enc = AMF_EncodeString(enc, pend, &av_secureTokenResponse);
    enc = AMF_EncodeNumber(enc, pend, 0.0);
    *enc++ = AMF_NULL;
    enc = AMF_EncodeString(enc, pend, resp);
    if (!enc)
        return FALSE;

    packet.m_nBodySize = enc - packet.m_body;

    return RTMP_SendPacket(r, &packet, FALSE);
}