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
struct TYPE_5__ {TYPE_1__* m_pHeader; int /*<<< orphan*/  m_pEnvList; } ;
struct TYPE_4__ {scalar_t__ m_cntEnv; } ;
typedef  TYPE_2__ LSAPI_Request ;
typedef  int /*<<< orphan*/  LSAPI_CB_EnvHandler ;

/* Variables and functions */
 int EnvForeach (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,void*) ; 

int LSAPI_ForeachEnv_r( LSAPI_Request * pReq,
            LSAPI_CB_EnvHandler fn, void * arg )
{
    if ( !pReq || !fn )
        return -1;
    if ( pReq->m_pHeader->m_cntEnv > 0 )
    {
        return EnvForeach( pReq->m_pEnvList, pReq->m_pHeader->m_cntEnv,
                    fn, arg );
    }
    return 0;
}