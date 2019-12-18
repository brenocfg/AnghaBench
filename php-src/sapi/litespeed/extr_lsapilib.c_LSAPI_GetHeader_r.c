#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* m_pHttpHeader; TYPE_1__* m_pHeaderIndex; } ;
struct TYPE_4__ {int* m_headerOff; int* m_headerLen; } ;
typedef  TYPE_2__ LSAPI_Request ;

/* Variables and functions */
 unsigned int H_TRANSFER_ENCODING ; 

char * LSAPI_GetHeader_r( LSAPI_Request * pReq, int headerIndex )
{
    int off;
    if ( !pReq || ((unsigned int)headerIndex > H_TRANSFER_ENCODING) )
        return NULL;
    off = pReq->m_pHeaderIndex->m_headerOff[ headerIndex ];
    if ( !off )
        return NULL;
    if ( *(pReq->m_pHttpHeader + off
        + pReq->m_pHeaderIndex->m_headerLen[ headerIndex ]) )
    {
        *( pReq->m_pHttpHeader + off
            + pReq->m_pHeaderIndex->m_headerLen[ headerIndex ]) = 0;
    }
    return pReq->m_pHttpHeader + off;
}