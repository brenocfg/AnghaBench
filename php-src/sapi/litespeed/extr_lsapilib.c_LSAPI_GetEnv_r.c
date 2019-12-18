#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct LSAPI_key_value_pair {char* pValue; int /*<<< orphan*/  pKey; } ;
struct TYPE_6__ {TYPE_1__* m_pHeader; struct LSAPI_key_value_pair* m_pEnvList; } ;
struct TYPE_5__ {int m_cntEnv; } ;
typedef  TYPE_2__ LSAPI_Request ;

/* Variables and functions */
 char* GetHeaderVar (TYPE_2__*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

char * LSAPI_GetEnv_r( LSAPI_Request * pReq, const char * name )
{
    struct LSAPI_key_value_pair * pBegin = pReq->m_pEnvList;
    struct LSAPI_key_value_pair * pEnd = pBegin + pReq->m_pHeader->m_cntEnv;
    if ( !pReq || !name )
        return NULL;
    if ( strncmp( name, "HTTP_", 5 ) == 0 )
    {
        return GetHeaderVar( pReq, name );
    }
    while( pBegin < pEnd )
    {
        if ( strcmp( name, pBegin->pKey ) == 0 )
            return pBegin->pValue;
        ++pBegin;
    }
    return NULL;
}