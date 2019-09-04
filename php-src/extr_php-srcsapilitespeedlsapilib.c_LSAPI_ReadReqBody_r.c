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
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_3__ {int m_fd; scalar_t__ m_reqBodyLen; scalar_t__ m_reqBodyRead; scalar_t__ m_bufRead; scalar_t__ m_bufProcessed; scalar_t__ m_pReqBuf; } ;
typedef  TYPE_1__ LSAPI_Request ;

/* Variables and functions */
 scalar_t__ lsapi_read (int,char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,scalar_t__,scalar_t__) ; 

ssize_t LSAPI_ReadReqBody_r( LSAPI_Request * pReq, char * pBuf, size_t bufLen )
{
    ssize_t len;
    off_t total;
    /* char *pOldBuf = pBuf; */
    if (!pReq || pReq->m_fd == -1 || !pBuf || (ssize_t)bufLen < 0)
        return -1;

    total = pReq->m_reqBodyLen - pReq->m_reqBodyRead;

    if ( total <= 0 )
        return 0;
    if ( total < (ssize_t)bufLen )
        bufLen = total;

    total = 0;
    len = pReq->m_bufRead - pReq->m_bufProcessed;
    if ( len > 0 )
    {
        if ( len > (ssize_t)bufLen )
            len = bufLen;
        memmove( pBuf, pReq->m_pReqBuf + pReq->m_bufProcessed, len );
        pReq->m_bufProcessed += len;
        total += len;
        pBuf += len;
        bufLen -= len;
    }
    while( bufLen > 0 )
    {
        len = lsapi_read( pReq->m_fd, pBuf, bufLen );
        if ( len > 0 )
        {
            total += len;
            pBuf += len;
            bufLen -= len;
        }
        else if ( len <= 0 )
        {
            if ( !total)
                return -1;
            break;
        }
    }
    pReq->m_reqBodyRead += total;
    return total;

}