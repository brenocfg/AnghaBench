#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int m_fd; scalar_t__ m_bufProcessed; scalar_t__ m_bufRead; scalar_t__* m_pReqBuf; int /*<<< orphan*/  m_reqBodyRead; } ;
typedef  TYPE_1__ LSAPI_Request ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ readBodyToReqBuf (TYPE_1__*) ; 

int LSAPI_ReqBodyGetChar_r( LSAPI_Request * pReq )
{
    if (!pReq || (pReq->m_fd ==-1) )
        return EOF;
    if ( pReq->m_bufProcessed >= pReq->m_bufRead )
    {
        if ( readBodyToReqBuf( pReq ) <= 0 )
            return EOF;
    }
    ++pReq->m_reqBodyRead;
    return (unsigned char)*(pReq->m_pReqBuf + pReq->m_bufProcessed++);
}