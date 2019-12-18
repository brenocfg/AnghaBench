#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lsapi_header_offset {int nameOff; int nameLen; int valueOff; int valueLen; } ;
struct TYPE_7__ {TYPE_2__* m_pHeader; struct lsapi_header_offset* m_pUnknownHeader; TYPE_1__* m_pHeaderIndex; } ;
struct TYPE_6__ {int m_httpHeaderLen; scalar_t__ m_cntUnknownHeaders; } ;
struct TYPE_5__ {int* m_headerOff; int* m_headerLen; } ;
typedef  TYPE_3__ LSAPI_Request ;

/* Variables and functions */
 int H_TRANSFER_ENCODING ; 

__attribute__((used)) static int validateHeaders( LSAPI_Request * pReq )
{
    int totalLen = pReq->m_pHeader->m_httpHeaderLen;
    int i;
    for(i = 0; i < H_TRANSFER_ENCODING; ++i)
    {
        if ( pReq->m_pHeaderIndex->m_headerOff[i] )
        {
            if (pReq->m_pHeaderIndex->m_headerOff[i] > totalLen
                || pReq->m_pHeaderIndex->m_headerLen[i]
                    + pReq->m_pHeaderIndex->m_headerOff[i] > totalLen)
                return -1;
        }
    }
    if (pReq->m_pHeader->m_cntUnknownHeaders > 0)
    {
        struct lsapi_header_offset * pCur, *pEnd;
        pCur = pReq->m_pUnknownHeader;
        pEnd = pCur + pReq->m_pHeader->m_cntUnknownHeaders;
        while( pCur < pEnd )
        {
            if (pCur->nameOff > totalLen
                || pCur->nameOff + pCur->nameLen > totalLen
                || pCur->valueOff > totalLen
                || pCur->valueOff + pCur->valueLen > totalLen)
                return -1;
            ++pCur;
        }
    }
    return 0;
}