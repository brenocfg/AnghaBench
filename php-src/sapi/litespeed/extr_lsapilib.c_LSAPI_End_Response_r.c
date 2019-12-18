#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int m_reqState; int m_fd; scalar_t__ m_pRespHeaderBufPos; scalar_t__ m_pRespHeaderBuf; scalar_t__ m_pRespBufPos; scalar_t__ m_pRespBuf; int m_totalLen; TYPE_1__* m_pIovecCur; } ;
struct TYPE_8__ {int iov_len; void* iov_base; } ;
typedef  TYPE_2__ LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  Flush_RespBuf_r (TYPE_2__*) ; 
 int /*<<< orphan*/  LSAPI_FinalizeRespHeaders_r (TYPE_2__*) ; 
 int /*<<< orphan*/  LSAPI_Flush_r (TYPE_2__*) ; 
 int LSAPI_PACKET_HEADER_LEN ; 
 int LSAPI_ST_BACKGROUND ; 
 int LSAPI_ST_RESP_HEADER ; 
 scalar_t__ finish_close ; 
 int /*<<< orphan*/  lsapi_close_connection (TYPE_2__*) ; 

int LSAPI_End_Response_r(LSAPI_Request * pReq)
{
    if (!pReq)
        return -1;
    if (pReq->m_reqState & LSAPI_ST_BACKGROUND)
        return 0;
    if (pReq->m_reqState)
    {
        if ( pReq->m_fd != -1 )
        {
            if ( pReq->m_reqState & LSAPI_ST_RESP_HEADER )
            {
                if ( pReq->m_pRespHeaderBufPos <= pReq->m_pRespHeaderBuf )
                    return 0;

                LSAPI_FinalizeRespHeaders_r( pReq );
            }
            if ( pReq->m_pRespBufPos != pReq->m_pRespBuf )
            {
                Flush_RespBuf_r( pReq );
            }

            pReq->m_pIovecCur->iov_base = (void *)finish_close;
            pReq->m_pIovecCur->iov_len  = LSAPI_PACKET_HEADER_LEN << 1;
            pReq->m_totalLen += LSAPI_PACKET_HEADER_LEN << 1;
            ++pReq->m_pIovecCur;
            LSAPI_Flush_r( pReq );
            lsapi_close_connection(pReq);
        }
        pReq->m_reqState |= LSAPI_ST_BACKGROUND;
    }
    return 0;
}