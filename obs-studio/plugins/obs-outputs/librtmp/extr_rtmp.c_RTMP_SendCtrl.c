#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  pbuf ;
struct TYPE_7__ {int /*<<< orphan*/  SWFVerificationResponse; } ;
struct TYPE_9__ {TYPE_1__ Link; } ;
struct TYPE_8__ {int m_nChannel; char* m_body; int m_nBodySize; scalar_t__ m_hasAbsTimestamp; scalar_t__ m_nInfoField2; scalar_t__ m_nTimeStamp; int /*<<< orphan*/  m_packetType; int /*<<< orphan*/  m_headerType; } ;
typedef  TYPE_2__ RTMPPacket ;
typedef  TYPE_3__ RTMP ;

/* Variables and functions */
 char* AMF_EncodeInt16 (char*,char*,short) ; 
 char* AMF_EncodeInt32 (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RTMP_LOGDEBUG ; 
 int /*<<< orphan*/  RTMP_Log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  RTMP_LogHex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int RTMP_MAX_HEADER_SIZE ; 
 int /*<<< orphan*/  RTMP_PACKET_SIZE_MEDIUM ; 
 int /*<<< orphan*/  RTMP_PACKET_TYPE_CONTROL ; 
 int RTMP_SendPacket (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

int
RTMP_SendCtrl(RTMP *r, short nType, unsigned int nObject, unsigned int nTime)
{
    RTMPPacket packet;
    char pbuf[256], *pend = pbuf + sizeof(pbuf);
    int nSize;
    char *buf;

    RTMP_Log(RTMP_LOGDEBUG, "sending ctrl. type: 0x%04x", (unsigned short)nType);

    packet.m_nChannel = 0x02;	/* control channel (ping) */
    packet.m_headerType = RTMP_PACKET_SIZE_MEDIUM;
    packet.m_packetType = RTMP_PACKET_TYPE_CONTROL;
    packet.m_nTimeStamp = 0;	/* RTMP_GetTime(); */
    packet.m_nInfoField2 = 0;
    packet.m_hasAbsTimestamp = 0;
    packet.m_body = pbuf + RTMP_MAX_HEADER_SIZE;

    switch(nType)
    {
    case 0x03:
        nSize = 10;
        break;	/* buffer time */
    case 0x1A:
        nSize = 3;
        break;	/* SWF verify request */
    case 0x1B:
        nSize = 44;
        break;	/* SWF verify response */
    default:
        nSize = 6;
        break;
    }

    packet.m_nBodySize = nSize;

    buf = packet.m_body;
    buf = AMF_EncodeInt16(buf, pend, nType);

    if (nType == 0x1B)
    {
#ifdef CRYPTO
        memcpy(buf, r->Link.SWFVerificationResponse, 42);
        RTMP_Log(RTMP_LOGDEBUG, "Sending SWFVerification response: ");
        RTMP_LogHex(RTMP_LOGDEBUG, (uint8_t *)packet.m_body, packet.m_nBodySize);
#endif
    }
    else if (nType == 0x1A)
    {
        *buf = nObject & 0xff;
    }
    else
    {
        if (nSize > 2)
            buf = AMF_EncodeInt32(buf, pend, nObject);

        if (nSize > 6)
            buf = AMF_EncodeInt32(buf, pend, nTime);
    }

    return RTMP_SendPacket(r, &packet, FALSE);
}