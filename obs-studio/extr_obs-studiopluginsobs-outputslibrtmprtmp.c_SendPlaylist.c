#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pbuf ;
struct TYPE_9__ {TYPE_1__* streams; } ;
struct TYPE_11__ {TYPE_2__ Link; } ;
struct TYPE_10__ {int m_nChannel; char* m_body; int m_nBodySize; scalar_t__ m_hasAbsTimestamp; int /*<<< orphan*/  m_nInfoField2; scalar_t__ m_nTimeStamp; int /*<<< orphan*/  m_packetType; int /*<<< orphan*/  m_headerType; } ;
struct TYPE_8__ {int /*<<< orphan*/  playpath; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ RTMPPacket ;
typedef  TYPE_4__ RTMP ;

/* Variables and functions */
 int /*<<< orphan*/  AMF_ECMA_ARRAY ; 
 char* AMF_EncodeNamedString (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* AMF_EncodeNumber (char*,char*,int /*<<< orphan*/ ) ; 
 char* AMF_EncodeString (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AMF_NULL ; 
 int /*<<< orphan*/  AMF_OBJECT ; 
 int /*<<< orphan*/  AMF_OBJECT_END ; 
 int FALSE ; 
 int RTMP_MAX_HEADER_SIZE ; 
 int /*<<< orphan*/  RTMP_PACKET_SIZE_LARGE ; 
 int /*<<< orphan*/  RTMP_PACKET_TYPE_INVOKE ; 
 int RTMP_SendPacket (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  av_0 ; 
 int /*<<< orphan*/  av_set_playlist ; 

__attribute__((used)) static int
SendPlaylist(RTMP *r, int streamIdx)
{
    RTMPPacket packet;
    char pbuf[1024], *pend = pbuf + sizeof(pbuf);
    char *enc;

    packet.m_nChannel = 0x08;	/* we make 8 our stream channel */
    packet.m_headerType = RTMP_PACKET_SIZE_LARGE;
    packet.m_packetType = RTMP_PACKET_TYPE_INVOKE;
    packet.m_nTimeStamp = 0;
    packet.m_nInfoField2 = r->Link.streams[streamIdx].id; /*0x01000000; */
    packet.m_hasAbsTimestamp = 0;
    packet.m_body = pbuf + RTMP_MAX_HEADER_SIZE;

    enc = packet.m_body;
    enc = AMF_EncodeString(enc, pend, &av_set_playlist);
    enc = AMF_EncodeNumber(enc, pend, 0);
    *enc++ = AMF_NULL;
    *enc++ = AMF_ECMA_ARRAY;
    *enc++ = 0;
    *enc++ = 0;
    *enc++ = 0;
    *enc++ = AMF_OBJECT;
    enc = AMF_EncodeNamedString(enc, pend, &av_0, &r->Link.streams[streamIdx].playpath);
    if (!enc)
        return FALSE;
    if (enc + 3 >= pend)
        return FALSE;
    *enc++ = 0;
    *enc++ = 0;
    *enc++ = AMF_OBJECT_END;

    packet.m_nBodySize = enc - packet.m_body;

    return RTMP_SendPacket(r, &packet, TRUE);
}