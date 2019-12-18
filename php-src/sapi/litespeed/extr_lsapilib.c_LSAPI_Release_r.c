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
struct TYPE_3__ {scalar_t__ m_pRespHeaderBuf; scalar_t__ m_pEnvList; scalar_t__ m_pSpecialEnvList; scalar_t__ m_pReqBuf; } ;
typedef  TYPE_1__ LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 

int LSAPI_Release_r( LSAPI_Request * pReq )
{
    if ( pReq->m_pReqBuf )
        free( pReq->m_pReqBuf );
    if ( pReq->m_pSpecialEnvList )
        free( pReq->m_pSpecialEnvList );
    if ( pReq->m_pEnvList )
        free( pReq->m_pEnvList );
    if ( pReq->m_pRespHeaderBuf )
        free( pReq->m_pRespHeaderBuf );
    return 0;
}