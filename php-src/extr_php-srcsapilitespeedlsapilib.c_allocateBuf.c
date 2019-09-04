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
struct lsapi_req_header {int dummy; } ;
struct TYPE_3__ {char* m_pReqBuf; int m_reqBufSize; struct lsapi_req_header* m_pHeader; } ;
typedef  TYPE_1__ LSAPI_Request ;

/* Variables and functions */
 scalar_t__ realloc (char*,int) ; 

__attribute__((used)) static inline int allocateBuf( LSAPI_Request * pReq, int size )
{
    char * pBuf = (char *)realloc( pReq->m_pReqBuf, size );
    if ( pBuf )
    {
        pReq->m_pReqBuf = pBuf;
        pReq->m_reqBufSize = size;
        pReq->m_pHeader = (struct lsapi_req_header *)pReq->m_pReqBuf;
        return 0;
    }
    return -1;
}