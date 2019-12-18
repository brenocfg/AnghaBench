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
struct TYPE_3__ {int /*<<< orphan*/  m_pHeaderIndex; scalar_t__ m_respHeaderLen; int /*<<< orphan*/  m_pRespHeaderBuf; int /*<<< orphan*/  m_pRespHeaderBufPos; scalar_t__ m_pIovec; scalar_t__ m_pIovecToWrite; scalar_t__ m_pIovecCur; int /*<<< orphan*/  m_pRespBuf; int /*<<< orphan*/  m_pRespBufPos; } ;
typedef  TYPE_1__ LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void LSAPI_Reset_r( LSAPI_Request * pReq )
{
    pReq->m_pRespBufPos         = pReq->m_pRespBuf;
    pReq->m_pIovecCur           = pReq->m_pIovecToWrite = pReq->m_pIovec + 1;
    pReq->m_pRespHeaderBufPos   = pReq->m_pRespHeaderBuf;

    memset( &pReq->m_pHeaderIndex, 0,
            (char *)(pReq->m_respHeaderLen) - (char *)&pReq->m_pHeaderIndex );
}