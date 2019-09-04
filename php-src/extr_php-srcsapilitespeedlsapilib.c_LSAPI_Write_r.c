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
struct lsapi_packet_header {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_7__ {int m_reqState; int m_fd; int m_pRespBufEnd; int m_pRespBufPos; int m_pRespBuf; struct lsapi_packet_header* m_respPktHeader; struct lsapi_packet_header* m_respPktHeaderEnd; TYPE_1__* m_pIovecCur; int /*<<< orphan*/  m_totalLen; } ;
struct TYPE_6__ {int iov_len; void* iov_base; } ;
typedef  TYPE_2__ LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_FinalizeRespHeaders_r (TYPE_2__*) ; 
 int LSAPI_Flush_r (TYPE_2__*) ; 
 int LSAPI_MAX_DATA_PACKET_LEN ; 
 int LSAPI_PACKET_HEADER_LEN ; 
 int /*<<< orphan*/  LSAPI_RESP_STREAM ; 
 int LSAPI_ST_BACKGROUND ; 
 int LSAPI_ST_RESP_BODY ; 
 int LSAPI_ST_RESP_HEADER ; 
 int /*<<< orphan*/  lsapi_buildPacketHeader (struct lsapi_packet_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (int,char const*,size_t) ; 

ssize_t LSAPI_Write_r( LSAPI_Request * pReq, const char * pBuf, size_t len )
{
    struct lsapi_packet_header * pHeader;
    const char * pEnd;
    const char * p;
    ssize_t bufLen;
    ssize_t toWrite;
    ssize_t packetLen;
    int skip = 0;

    if (!pReq || !pBuf)
        return -1;
    if (pReq->m_reqState & LSAPI_ST_BACKGROUND)
        return len;
    if (pReq->m_fd == -1)
        return -1;
    if ( pReq->m_reqState & LSAPI_ST_RESP_HEADER )
    {
        LSAPI_FinalizeRespHeaders_r( pReq );
/*
        if ( *pBuf == '\r' )
        {
            ++skip;
        }
        if ( *pBuf == '\n' )
        {
            ++skip;
        }
*/
    }
    pReq->m_reqState |= LSAPI_ST_RESP_BODY;

    if ( ((ssize_t)len - skip) < pReq->m_pRespBufEnd - pReq->m_pRespBufPos )
    {
        memmove( pReq->m_pRespBufPos, pBuf + skip, len - skip );
        pReq->m_pRespBufPos += len - skip;
        return len;
    }


    pHeader = pReq->m_respPktHeader;
    p       = pBuf + skip;
    pEnd    = pBuf + len;
    bufLen  = pReq->m_pRespBufPos - pReq->m_pRespBuf;

    while( ( toWrite = pEnd - p ) > 0 )
    {
        packetLen = toWrite + bufLen;
        if ( LSAPI_MAX_DATA_PACKET_LEN < packetLen)
        {
            packetLen = LSAPI_MAX_DATA_PACKET_LEN;
            toWrite = packetLen - bufLen;
        }

        lsapi_buildPacketHeader( pHeader, LSAPI_RESP_STREAM,
                            packetLen + LSAPI_PACKET_HEADER_LEN );
        pReq->m_totalLen += packetLen + LSAPI_PACKET_HEADER_LEN;

        pReq->m_pIovecCur->iov_base = (void *)pHeader;
        pReq->m_pIovecCur->iov_len  = LSAPI_PACKET_HEADER_LEN;
        ++pReq->m_pIovecCur;
        ++pHeader;
        if ( bufLen > 0 )
        {
            pReq->m_pIovecCur->iov_base = (void *)pReq->m_pRespBuf;
            pReq->m_pIovecCur->iov_len  = bufLen;
            pReq->m_pRespBufPos = pReq->m_pRespBuf;
            ++pReq->m_pIovecCur;
            bufLen = 0;
        }

        pReq->m_pIovecCur->iov_base = (void *)p;
        pReq->m_pIovecCur->iov_len  = toWrite;
        ++pReq->m_pIovecCur;
        p += toWrite;

        if ( pHeader >= pReq->m_respPktHeaderEnd - 1)
        {
            if ( LSAPI_Flush_r( pReq ) == -1 )
                return -1;
            pHeader = pReq->m_respPktHeader;
        }
    }
    if ( pHeader != pReq->m_respPktHeader )
        if ( LSAPI_Flush_r( pReq ) == -1 )
            return -1;
    return p - pBuf;
}