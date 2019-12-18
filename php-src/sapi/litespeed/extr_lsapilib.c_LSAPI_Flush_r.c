#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int m_pIovecCur; int m_pIovecToWrite; scalar_t__ m_pRespBufPos; scalar_t__ m_pRespBuf; int m_fd; int m_totalLen; int m_pIovec; int m_reqState; } ;
typedef  TYPE_1__ LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  Flush_RespBuf_r (TYPE_1__*) ; 
 int /*<<< orphan*/  LSAPI_FinalizeRespHeaders_r (TYPE_1__*) ; 
 int LSAPI_ST_RESP_HEADER ; 
 int /*<<< orphan*/  lsapi_close_connection (TYPE_1__*) ; 
 int lsapi_writev (int,int*,int,int) ; 

int LSAPI_Flush_r( LSAPI_Request * pReq )
{
    int ret = 0;
    int n;
    if ( !pReq )
        return -1;
    n = pReq->m_pIovecCur - pReq->m_pIovecToWrite;
    if (( 0 == n )&&( pReq->m_pRespBufPos == pReq->m_pRespBuf ))
        return 0;
    if ( pReq->m_fd == -1 )
    {
        pReq->m_pRespBufPos = pReq->m_pRespBuf;
        pReq->m_totalLen = 0;
        pReq->m_pIovecCur = pReq->m_pIovecToWrite = pReq->m_pIovec;
        return -1;
    }
    if ( pReq->m_reqState & LSAPI_ST_RESP_HEADER )
    {
        LSAPI_FinalizeRespHeaders_r( pReq );
    }
    if ( pReq->m_pRespBufPos != pReq->m_pRespBuf )
    {
        Flush_RespBuf_r( pReq );
    }

    n = pReq->m_pIovecCur - pReq->m_pIovecToWrite;
    if ( n > 0 )
    {

        ret = lsapi_writev( pReq->m_fd, &pReq->m_pIovecToWrite,
                  n, pReq->m_totalLen );
        if ( ret < pReq->m_totalLen )
        {
            lsapi_close_connection(pReq);
            ret = -1;
        }
        pReq->m_totalLen = 0;
        pReq->m_pIovecCur = pReq->m_pIovecToWrite = pReq->m_pIovec;
    }
    return ret;
}