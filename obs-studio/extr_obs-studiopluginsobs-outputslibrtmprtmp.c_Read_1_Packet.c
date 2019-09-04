#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char uint32_t ;
struct TYPE_10__ {int dataType; int flags; unsigned int nMetaHeaderSize; unsigned int nInitialFrameSize; char initialFrameType; char nResumeTS; scalar_t__ nIgnoredFrameCounter; scalar_t__ nIgnoredFlvFrameCounter; char* buf; char timestamp; char* bufpos; int buflen; int /*<<< orphan*/  initialFrame; int /*<<< orphan*/  metaHeader; } ;
struct TYPE_9__ {int lFlags; } ;
struct TYPE_12__ {TYPE_2__ m_read; TYPE_1__ Link; } ;
struct TYPE_11__ {char* m_body; unsigned int m_nBodySize; char m_packetType; int m_nTimeStamp; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ RTMPPacket ;
typedef  TYPE_4__ RTMP ;
typedef  int /*<<< orphan*/  AVal ;
typedef  int /*<<< orphan*/  AMFObject ;

/* Variables and functions */
 int /*<<< orphan*/  AMFProp_GetString (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int AMF_Decode (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 char AMF_DecodeInt24 (char*) ; 
 char AMF_DecodeInt32 (char*) ; 
 char* AMF_EncodeInt24 (char*,char*,char) ; 
 int /*<<< orphan*/  AMF_EncodeInt32 (char*,char*,char) ; 
 int /*<<< orphan*/  AMF_GetProp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMF_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ AVMATCH (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 scalar_t__ MAX_IGNORED_FRAMES ; 
 int /*<<< orphan*/  RTMPPacket_Free (TYPE_3__*) ; 
 int RTMP_GetNextMediaPacket (TYPE_4__*,TYPE_3__*) ; 
 int RTMP_LF_LIVE ; 
 int /*<<< orphan*/  RTMP_LOGDEBUG ; 
 int /*<<< orphan*/  RTMP_LOGERROR ; 
 int /*<<< orphan*/  RTMP_LOGWARNING ; 
 int /*<<< orphan*/  RTMP_Log (int /*<<< orphan*/ ,char*,...) ; 
 char RTMP_PACKET_TYPE_AUDIO ; 
 char RTMP_PACKET_TYPE_FLASH_VIDEO ; 
 char RTMP_PACKET_TYPE_INFO ; 
 char RTMP_PACKET_TYPE_VIDEO ; 
 int RTMP_READ_COMPLETE ; 
 int RTMP_READ_EOF ; 
 int RTMP_READ_ERROR ; 
 int RTMP_READ_GOTFLVK ; 
 int RTMP_READ_GOTKF ; 
 int RTMP_READ_IGNORE ; 
 int RTMP_READ_NO_IGNORE ; 
 int RTMP_READ_RESUME ; 
 int RTMP_READ_SEEKING ; 
 int TRUE ; 
 int /*<<< orphan*/  av_onMetaData ; 
 char* malloc (unsigned int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 

__attribute__((used)) static int
Read_1_Packet(RTMP *r, char *buf, unsigned int buflen)
{
    uint32_t prevTagSize = 0;
    int rtnGetNextMediaPacket = 0, ret = RTMP_READ_EOF;
    RTMPPacket packet = { 0 };
    int recopy = FALSE;
    unsigned int size;
    char *ptr, *pend;
    uint32_t nTimeStamp = 0;
    unsigned int len;

    rtnGetNextMediaPacket = RTMP_GetNextMediaPacket(r, &packet);
    while (rtnGetNextMediaPacket)
    {
        char *packetBody = packet.m_body;
        unsigned int nPacketLen = packet.m_nBodySize;

        /* Return RTMP_READ_COMPLETE if this was completed nicely with
         * invoke message Play.Stop or Play.Complete
         */
        if (rtnGetNextMediaPacket == 2)
        {
            RTMP_Log(RTMP_LOGDEBUG,
                     "Got Play.Complete or Play.Stop from server. "
                     "Assuming stream is complete");
            ret = RTMP_READ_COMPLETE;
            break;
        }

        r->m_read.dataType |= (((packet.m_packetType == RTMP_PACKET_TYPE_AUDIO) << 2) |
                               (packet.m_packetType == RTMP_PACKET_TYPE_VIDEO));

        if (packet.m_packetType == RTMP_PACKET_TYPE_VIDEO && nPacketLen <= 5)
        {
            RTMP_Log(RTMP_LOGDEBUG, "ignoring too small video packet: size: %d",
                     nPacketLen);
            ret = RTMP_READ_IGNORE;
            break;
        }
        if (packet.m_packetType == RTMP_PACKET_TYPE_AUDIO && nPacketLen <= 1)
        {
            RTMP_Log(RTMP_LOGDEBUG, "ignoring too small audio packet: size: %d",
                     nPacketLen);
            ret = RTMP_READ_IGNORE;
            break;
        }

        if (r->m_read.flags & RTMP_READ_SEEKING)
        {
            ret = RTMP_READ_IGNORE;
            break;
        }
#ifdef _DEBUG
        RTMP_Log(RTMP_LOGDEBUG, "type: %02X, size: %d, TS: %d ms, abs TS: %d",
                 packet.m_packetType, nPacketLen, packet.m_nTimeStamp,
                 packet.m_hasAbsTimestamp);
        if (packet.m_packetType == RTMP_PACKET_TYPE_VIDEO)
            RTMP_Log(RTMP_LOGDEBUG, "frametype: %02X", (*packetBody & 0xf0));
#endif

        if (r->m_read.flags & RTMP_READ_RESUME)
        {
            /* check the header if we get one */
            if (packet.m_nTimeStamp == 0)
            {
                if (r->m_read.nMetaHeaderSize > 0
                        && packet.m_packetType == RTMP_PACKET_TYPE_INFO)
                {
                    AMFObject metaObj;
                    int nRes =
                        AMF_Decode(&metaObj, packetBody, nPacketLen, FALSE);
                    if (nRes >= 0)
                    {
                        AVal metastring;
                        AMFProp_GetString(AMF_GetProp(&metaObj, NULL, 0),
                                          &metastring);

                        if (AVMATCH(&metastring, &av_onMetaData))
                        {
                            /* compare */
                            if ((r->m_read.nMetaHeaderSize != nPacketLen) ||
                                    (memcmp
                                     (r->m_read.metaHeader, packetBody,
                                      r->m_read.nMetaHeaderSize) != 0))
                            {
                                ret = RTMP_READ_ERROR;
                            }
                        }
                        AMF_Reset(&metaObj);
                        if (ret == RTMP_READ_ERROR)
                            break;
                    }
                }

                /* check first keyframe to make sure we got the right position
                 * in the stream! (the first non ignored frame)
                 */
                if (r->m_read.nInitialFrameSize > 0)
                {
                    /* video or audio data */
                    if (packet.m_packetType == r->m_read.initialFrameType
                            && r->m_read.nInitialFrameSize == nPacketLen)
                    {
                        /* we don't compare the sizes since the packet can
                         * contain several FLV packets, just make sure the
                         * first frame is our keyframe (which we are going
                         * to rewrite)
                         */
                        if (memcmp
                                (r->m_read.initialFrame, packetBody,
                                 r->m_read.nInitialFrameSize) == 0)
                        {
                            RTMP_Log(RTMP_LOGDEBUG, "Checked keyframe successfully!");
                            r->m_read.flags |= RTMP_READ_GOTKF;
                            /* ignore it! (what about audio data after it? it is
                             * handled by ignoring all 0ms frames, see below)
                             */
                            ret = RTMP_READ_IGNORE;
                            break;
                        }
                    }

                    /* hande FLV streams, even though the server resends the
                     * keyframe as an extra video packet it is also included
                     * in the first FLV stream chunk and we have to compare
                     * it and filter it out !!
                     */
                    if (packet.m_packetType == RTMP_PACKET_TYPE_FLASH_VIDEO)
                    {
                        /* basically we have to find the keyframe with the
                         * correct TS being nResumeTS
                         */
                        unsigned int pos = 0;
                        uint32_t ts = 0;

                        while (pos + 11 < nPacketLen)
                        {
                            /* size without header (11) and prevTagSize (4) */
                            uint32_t dataSize =
                                AMF_DecodeInt24(packetBody + pos + 1);
                            ts = AMF_DecodeInt24(packetBody + pos + 4);
                            ts |= (packetBody[pos + 7] << 24);

#ifdef _DEBUG
                            RTMP_Log(RTMP_LOGDEBUG,
                                     "keyframe search: FLV Packet: type %02X, dataSize: %d, timeStamp: %d ms",
                                     packetBody[pos], dataSize, ts);
#endif
                            /* ok, is it a keyframe?:
                             * well doesn't work for audio!
                             */
                            if (packetBody[pos /*6928, test 0 */ ] ==
                                    r->m_read.initialFrameType
                                    /* && (packetBody[11]&0xf0) == 0x10 */ )
                            {
                                if (ts == r->m_read.nResumeTS)
                                {
                                    RTMP_Log(RTMP_LOGDEBUG,
                                             "Found keyframe with resume-keyframe timestamp!");
                                    if (r->m_read.nInitialFrameSize != dataSize
                                            || memcmp(r->m_read.initialFrame,
                                                      packetBody + pos + 11,
                                                      r->m_read.
                                                      nInitialFrameSize) != 0)
                                    {
                                        RTMP_Log(RTMP_LOGERROR,
                                                 "FLV Stream: Keyframe doesn't match!");
                                        ret = RTMP_READ_ERROR;
                                        break;
                                    }
                                    r->m_read.flags |= RTMP_READ_GOTFLVK;

                                    /* skip this packet?
                                     * check whether skippable:
                                     */
                                    if (pos + 11 + dataSize + 4 > nPacketLen)
                                    {
                                        RTMP_Log(RTMP_LOGWARNING,
                                                 "Non skipable packet since it doesn't end with chunk, stream corrupt!");
                                        ret = RTMP_READ_ERROR;
                                        break;
                                    }
                                    packetBody += (pos + 11 + dataSize + 4);
                                    nPacketLen -= (pos + 11 + dataSize + 4);

                                    goto stopKeyframeSearch;

                                }
                                else if (r->m_read.nResumeTS < ts)
                                {
                                    /* the timestamp ts will only increase with
                                     * further packets, wait for seek
                                     */
                                    goto stopKeyframeSearch;
                                }
                            }
                            pos += (11 + dataSize + 4);
                        }
                        if (ts < r->m_read.nResumeTS)
                        {
                            RTMP_Log(RTMP_LOGERROR,
                                     "First packet does not contain keyframe, all "
                                     "timestamps are smaller than the keyframe "
                                     "timestamp; probably the resume seek failed?");
                        }
stopKeyframeSearch:
                        ;
                        if (!(r->m_read.flags & RTMP_READ_GOTFLVK))
                        {
                            RTMP_Log(RTMP_LOGERROR,
                                     "Couldn't find the seeked keyframe in this chunk!");
                            ret = RTMP_READ_IGNORE;
                            break;
                        }
                    }
                }
            }

            if (packet.m_nTimeStamp > 0
                    && (r->m_read.flags & (RTMP_READ_GOTKF|RTMP_READ_GOTFLVK)))
            {
                /* another problem is that the server can actually change from
                 * 09/08 video/audio packets to an FLV stream or vice versa and
                 * our keyframe check will prevent us from going along with the
                 * new stream if we resumed.
                 *
                 * in this case set the 'found keyframe' variables to true.
                 * We assume that if we found one keyframe somewhere and were
                 * already beyond TS > 0 we have written data to the output
                 * which means we can accept all forthcoming data including the
                 * change between 08/09 <-> FLV packets
                 */
                r->m_read.flags |= (RTMP_READ_GOTKF|RTMP_READ_GOTFLVK);
            }

            /* skip till we find our keyframe
             * (seeking might put us somewhere before it)
             */
            if (!(r->m_read.flags & RTMP_READ_GOTKF) &&
                    packet.m_packetType != RTMP_PACKET_TYPE_FLASH_VIDEO)
            {
                RTMP_Log(RTMP_LOGWARNING,
                         "Stream does not start with requested frame, ignoring data... ");
                r->m_read.nIgnoredFrameCounter++;
                if (r->m_read.nIgnoredFrameCounter > MAX_IGNORED_FRAMES)
                    ret = RTMP_READ_ERROR;	/* fatal error, couldn't continue stream */
                else
                    ret = RTMP_READ_IGNORE;
                break;
            }
            /* ok, do the same for FLV streams */
            if (!(r->m_read.flags & RTMP_READ_GOTFLVK) &&
                    packet.m_packetType == RTMP_PACKET_TYPE_FLASH_VIDEO)
            {
                RTMP_Log(RTMP_LOGWARNING,
                         "Stream does not start with requested FLV frame, ignoring data... ");
                r->m_read.nIgnoredFlvFrameCounter++;
                if (r->m_read.nIgnoredFlvFrameCounter > MAX_IGNORED_FRAMES)
                    ret = RTMP_READ_ERROR;
                else
                    ret = RTMP_READ_IGNORE;
                break;
            }

            /* we have to ignore the 0ms frames since these are the first
             * keyframes; we've got these so don't mess around with multiple
             * copies sent by the server to us! (if the keyframe is found at a
             * later position there is only one copy and it will be ignored by
             * the preceding if clause)
             */
            if (!(r->m_read.flags & RTMP_READ_NO_IGNORE) &&
                    packet.m_packetType != RTMP_PACKET_TYPE_FLASH_VIDEO)
            {
                /* exclude type RTMP_PACKET_TYPE_FLASH_VIDEO since it can
                 * contain several FLV packets
                 */
                if (packet.m_nTimeStamp == 0)
                {
                    ret = RTMP_READ_IGNORE;
                    break;
                }
                else
                {
                    /* stop ignoring packets */
                    r->m_read.flags |= RTMP_READ_NO_IGNORE;
                }
            }
        }

        /* calculate packet size and allocate slop buffer if necessary */
        size = nPacketLen +
               ((packet.m_packetType == RTMP_PACKET_TYPE_AUDIO
                 || packet.m_packetType == RTMP_PACKET_TYPE_VIDEO
                 || packet.m_packetType == RTMP_PACKET_TYPE_INFO) ? 11 : 0) +
               (packet.m_packetType != RTMP_PACKET_TYPE_FLASH_VIDEO ? 4 : 0);

        if (size + 4 > buflen)
        {
            /* the extra 4 is for the case of an FLV stream without a last
             * prevTagSize (we need extra 4 bytes to append it) */
            r->m_read.buf = malloc(size + 4);
            if (r->m_read.buf == 0)
            {
                RTMP_Log(RTMP_LOGERROR, "Couldn't allocate memory!");
                ret = RTMP_READ_ERROR;		/* fatal error */
                break;
            }
            recopy = TRUE;
            ptr = r->m_read.buf;
        }
        else
        {
            ptr = buf;
        }
        pend = ptr + size + 4;

        /* use to return timestamp of last processed packet */

        /* audio (0x08), video (0x09) or metadata (0x12) packets :
         * construct 11 byte header then add rtmp packet's data */
        if (packet.m_packetType == RTMP_PACKET_TYPE_AUDIO
                || packet.m_packetType == RTMP_PACKET_TYPE_VIDEO
                || packet.m_packetType == RTMP_PACKET_TYPE_INFO)
        {
            nTimeStamp = r->m_read.nResumeTS + packet.m_nTimeStamp;
            prevTagSize = 11 + nPacketLen;

            *ptr = packet.m_packetType;
            ptr++;
            ptr = AMF_EncodeInt24(ptr, pend, nPacketLen);

#if 0
            if(packet.m_packetType == RTMP_PACKET_TYPE_VIDEO)
            {

                /* H264 fix: */
                if((packetBody[0] & 0x0f) == 7)   /* CodecId = H264 */
                {
                    uint8_t packetType = *(packetBody+1);

                    uint32_t ts = AMF_DecodeInt24(packetBody+2); /* composition time */
                    int32_t cts = (ts+0xff800000)^0xff800000;
                    RTMP_Log(RTMP_LOGDEBUG, "cts  : %d\n", cts);

                    nTimeStamp -= cts;
                    /* get rid of the composition time */
                    CRTMP::EncodeInt24(packetBody+2, 0);
                }
                RTMP_Log(RTMP_LOGDEBUG, "VIDEO: nTimeStamp: 0x%08X (%d)\n", nTimeStamp, nTimeStamp);
            }
#endif

            ptr = AMF_EncodeInt24(ptr, pend, nTimeStamp);
            *ptr = (char)((nTimeStamp & 0xFF000000) >> 24);
            ptr++;

            /* stream id */
            ptr = AMF_EncodeInt24(ptr, pend, 0);
        }

        memcpy(ptr, packetBody, nPacketLen);
        len = nPacketLen;

        /* correct tagSize and obtain timestamp if we have an FLV stream */
        if (packet.m_packetType == RTMP_PACKET_TYPE_FLASH_VIDEO)
        {
            unsigned int pos = 0;
            int delta;

            /* grab first timestamp and see if it needs fixing */
            nTimeStamp = AMF_DecodeInt24(packetBody + 4);
            nTimeStamp |= (packetBody[7] << 24);
            delta = packet.m_nTimeStamp - nTimeStamp + r->m_read.nResumeTS;

            while (pos + 11 < nPacketLen)
            {
                /* size without header (11) and without prevTagSize (4) */
                uint32_t dataSize = AMF_DecodeInt24(packetBody + pos + 1);
                nTimeStamp = AMF_DecodeInt24(packetBody + pos + 4);
                nTimeStamp |= (packetBody[pos + 7] << 24);

                if (delta)
                {
                    nTimeStamp += delta;
                    AMF_EncodeInt24(ptr+pos+4, pend, nTimeStamp);
                    ptr[pos+7] = nTimeStamp>>24;
                }

                /* set data type */
                r->m_read.dataType |= (((*(packetBody + pos) == 0x08) << 2) |
                                       (*(packetBody + pos) == 0x09));

                if (pos + 11 + dataSize + 4 > nPacketLen)
                {
                    if (pos + 11 + dataSize > nPacketLen)
                    {
                        RTMP_Log(RTMP_LOGERROR,
                                 "Wrong data size (%u), stream corrupted, aborting!",
                                 dataSize);
                        ret = RTMP_READ_ERROR;
                        break;
                    }
                    RTMP_Log(RTMP_LOGWARNING, "No tagSize found, appending!");

                    /* we have to append a last tagSize! */
                    prevTagSize = dataSize + 11;
                    AMF_EncodeInt32(ptr + pos + 11 + dataSize, pend,
                                    prevTagSize);
                    size += 4;
                    len += 4;
                }
                else
                {
                    prevTagSize =
                        AMF_DecodeInt32(packetBody + pos + 11 + dataSize);

#ifdef _DEBUG
                    RTMP_Log(RTMP_LOGDEBUG,
                             "FLV Packet: type %02X, dataSize: %u, tagSize: %u, timeStamp: %u ms",
                             (unsigned char)packetBody[pos], dataSize, prevTagSize,
                             nTimeStamp);
#endif

                    if (prevTagSize != (dataSize + 11))
                    {
#ifdef _DEBUG
                        RTMP_Log(RTMP_LOGWARNING,
                                 "Tag and data size are not consitent, writing tag size according to dataSize+11: %d",
                                 dataSize + 11);
#endif

                        prevTagSize = dataSize + 11;
                        AMF_EncodeInt32(ptr + pos + 11 + dataSize, pend,
                                        prevTagSize);
                    }
                }

                pos += prevTagSize + 4;	/*(11+dataSize+4); */
            }
        }
        ptr += len;

        if (packet.m_packetType != RTMP_PACKET_TYPE_FLASH_VIDEO)
        {
            /* FLV tag packets contain their own prevTagSize */
            AMF_EncodeInt32(ptr, pend, prevTagSize);
        }

        /* In non-live this nTimeStamp can contain an absolute TS.
         * Update ext timestamp with this absolute offset in non-live mode
         * otherwise report the relative one
         */
        /* RTMP_Log(RTMP_LOGDEBUG, "type: %02X, size: %d, pktTS: %dms, TS: %dms, bLiveStream: %d", packet.m_packetType, nPacketLen, packet.m_nTimeStamp, nTimeStamp, r->Link.lFlags & RTMP_LF_LIVE); */
        r->m_read.timestamp = (r->Link.lFlags & RTMP_LF_LIVE) ? packet.m_nTimeStamp : nTimeStamp;

        ret = size;
        break;
    }

    if (rtnGetNextMediaPacket)
        RTMPPacket_Free(&packet);

    if (recopy)
    {
        len = ret > (int)(buflen) ? buflen : (unsigned int)(ret);
        memcpy(buf, r->m_read.buf, len);
        r->m_read.bufpos = r->m_read.buf + len;
        r->m_read.buflen = ret - len;
    }
    return ret;
}