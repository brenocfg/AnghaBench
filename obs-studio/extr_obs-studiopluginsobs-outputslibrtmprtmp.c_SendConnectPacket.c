#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pbuf ;
struct TYPE_18__ {scalar_t__ av_len; } ;
struct TYPE_17__ {scalar_t__ av_len; } ;
struct TYPE_13__ {int o_num; int /*<<< orphan*/ * o_props; } ;
struct TYPE_14__ {int protocol; int lFlags; TYPE_1__ extras; TYPE_6__ auth; TYPE_5__ pageUrl; TYPE_5__ tcUrl; TYPE_5__ swfUrl; TYPE_5__ flashVer; TYPE_5__ app; } ;
struct TYPE_16__ {double m_fAudioCodecs; double m_fVideoCodecs; double m_fEncoding; TYPE_2__ Link; scalar_t__ m_bSendEncoding; int /*<<< orphan*/  m_numInvokes; int /*<<< orphan*/  m_outChunkSize; scalar_t__ m_bSendChunkSizeInfo; } ;
struct TYPE_15__ {int m_nChannel; char* m_body; int m_nBodySize; scalar_t__ m_hasAbsTimestamp; scalar_t__ m_nInfoField2; scalar_t__ m_nTimeStamp; int /*<<< orphan*/  m_packetType; void* m_headerType; } ;
typedef  TYPE_3__ RTMPPacket ;
typedef  TYPE_4__ RTMP ;

/* Variables and functions */
 char* AMFProp_Encode (int /*<<< orphan*/ *,char*,char*) ; 
 char* AMF_EncodeBoolean (char*,char*,int) ; 
 int /*<<< orphan*/  AMF_EncodeInt32 (char*,char*,int /*<<< orphan*/ ) ; 
 char* AMF_EncodeNamedBoolean (char*,char*,int /*<<< orphan*/ *,int) ; 
 char* AMF_EncodeNamedNumber (char*,char*,int /*<<< orphan*/ *,double) ; 
 char* AMF_EncodeNamedString (char*,char*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 char* AMF_EncodeNumber (char*,char*,int /*<<< orphan*/ ) ; 
 char* AMF_EncodeString (char*,char*,TYPE_6__*) ; 
 int /*<<< orphan*/  AMF_OBJECT ; 
 int /*<<< orphan*/  AMF_OBJECT_END ; 
 int FALSE ; 
 int RTMP_FEATURE_WRITE ; 
 int RTMP_LF_AUTH ; 
 int RTMP_MAX_HEADER_SIZE ; 
 void* RTMP_PACKET_SIZE_LARGE ; 
 int /*<<< orphan*/  RTMP_PACKET_TYPE_CHUNK_SIZE ; 
 int /*<<< orphan*/  RTMP_PACKET_TYPE_INVOKE ; 
 int RTMP_SendPacket (TYPE_4__*,TYPE_3__*,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  av_app ; 
 int /*<<< orphan*/  av_audioCodecs ; 
 int /*<<< orphan*/  av_capabilities ; 
 TYPE_6__ av_connect ; 
 int /*<<< orphan*/  av_flashVer ; 
 int /*<<< orphan*/  av_fpad ; 
 TYPE_5__ av_nonprivate ; 
 int /*<<< orphan*/  av_objectEncoding ; 
 int /*<<< orphan*/  av_pageUrl ; 
 int /*<<< orphan*/  av_swfUrl ; 
 int /*<<< orphan*/  av_tcUrl ; 
 int /*<<< orphan*/  av_type ; 
 int /*<<< orphan*/  av_videoCodecs ; 
 int /*<<< orphan*/  av_videoFunction ; 

__attribute__((used)) static int
SendConnectPacket(RTMP *r, RTMPPacket *cp)
{
    RTMPPacket packet;
    char pbuf[4096], *pend = pbuf + sizeof(pbuf);
    char *enc;

    if (cp)
        return RTMP_SendPacket(r, cp, TRUE);

    if((r->Link.protocol & RTMP_FEATURE_WRITE) && r->m_bSendChunkSizeInfo)
    {
        packet.m_nChannel = 0x02;
        packet.m_headerType = RTMP_PACKET_SIZE_LARGE;
        packet.m_packetType = RTMP_PACKET_TYPE_CHUNK_SIZE;
        packet.m_nTimeStamp = 0;
        packet.m_nInfoField2 = 0;
        packet.m_hasAbsTimestamp = 0;
        packet.m_body = pbuf + RTMP_MAX_HEADER_SIZE;
        packet.m_nBodySize = 4;

        enc = packet.m_body;
        AMF_EncodeInt32(enc, pend, r->m_outChunkSize);

        if(!RTMP_SendPacket(r, &packet, FALSE))
            return 0;
    }

    packet.m_nChannel = 0x03;	/* control channel (invoke) */
    packet.m_headerType = RTMP_PACKET_SIZE_LARGE;
    packet.m_packetType = RTMP_PACKET_TYPE_INVOKE;
    packet.m_nTimeStamp = 0;
    packet.m_nInfoField2 = 0;
    packet.m_hasAbsTimestamp = 0;
    packet.m_body = pbuf + RTMP_MAX_HEADER_SIZE;

    enc = packet.m_body;
    enc = AMF_EncodeString(enc, pend, &av_connect);
    enc = AMF_EncodeNumber(enc, pend, ++r->m_numInvokes);
    *enc++ = AMF_OBJECT;

    enc = AMF_EncodeNamedString(enc, pend, &av_app, &r->Link.app);
    if (!enc)
        return FALSE;
    if (r->Link.protocol & RTMP_FEATURE_WRITE)
    {
        enc = AMF_EncodeNamedString(enc, pend, &av_type, &av_nonprivate);
        if (!enc)
            return FALSE;
    }
    if (r->Link.flashVer.av_len)
    {
        enc = AMF_EncodeNamedString(enc, pend, &av_flashVer, &r->Link.flashVer);
        if (!enc)
            return FALSE;
    }
    if (r->Link.swfUrl.av_len)
    {
        enc = AMF_EncodeNamedString(enc, pend, &av_swfUrl, &r->Link.swfUrl);
        if (!enc)
            return FALSE;
    }
    if (r->Link.tcUrl.av_len)
    {
        enc = AMF_EncodeNamedString(enc, pend, &av_tcUrl, &r->Link.tcUrl);
        if (!enc)
            return FALSE;
    }
    if (!(r->Link.protocol & RTMP_FEATURE_WRITE))
    {
        enc = AMF_EncodeNamedBoolean(enc, pend, &av_fpad, FALSE);
        if (!enc)
            return FALSE;
        enc = AMF_EncodeNamedNumber(enc, pend, &av_capabilities, 15.0);
        if (!enc)
            return FALSE;
        enc = AMF_EncodeNamedNumber(enc, pend, &av_audioCodecs, r->m_fAudioCodecs);
        if (!enc)
            return FALSE;
        enc = AMF_EncodeNamedNumber(enc, pend, &av_videoCodecs, r->m_fVideoCodecs);
        if (!enc)
            return FALSE;
        enc = AMF_EncodeNamedNumber(enc, pend, &av_videoFunction, 1.0);
        if (!enc)
            return FALSE;
        if (r->Link.pageUrl.av_len)
        {
            enc = AMF_EncodeNamedString(enc, pend, &av_pageUrl, &r->Link.pageUrl);
            if (!enc)
                return FALSE;
        }
    }
    if (r->m_fEncoding != 0.0 || r->m_bSendEncoding)
    {
        /* AMF0, AMF3 not fully supported yet */
        enc = AMF_EncodeNamedNumber(enc, pend, &av_objectEncoding, r->m_fEncoding);
        if (!enc)
            return FALSE;
    }
    if (enc + 3 >= pend)
        return FALSE;
    *enc++ = 0;
    *enc++ = 0;			/* end of object - 0x00 0x00 0x09 */
    *enc++ = AMF_OBJECT_END;

    /* add auth string */
    if (r->Link.auth.av_len)
    {
        enc = AMF_EncodeBoolean(enc, pend, r->Link.lFlags & RTMP_LF_AUTH);
        if (!enc)
            return FALSE;
        enc = AMF_EncodeString(enc, pend, &r->Link.auth);
        if (!enc)
            return FALSE;
    }
    if (r->Link.extras.o_num)
    {
        int i;
        for (i = 0; i < r->Link.extras.o_num; i++)
        {
            enc = AMFProp_Encode(&r->Link.extras.o_props[i], enc, pend);
            if (!enc)
                return FALSE;
        }
    }
    packet.m_nBodySize = enc - packet.m_body;

    return RTMP_SendPacket(r, &packet, TRUE);
}