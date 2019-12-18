#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct LSAPI_key_value_pair {int /*<<< orphan*/  valLen; int /*<<< orphan*/  pValue; int /*<<< orphan*/  keyLen; int /*<<< orphan*/  pKey; } ;
typedef  int (* LSAPI_CB_EnvHandler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int EnvForeach( struct LSAPI_key_value_pair * pEnv,
            int n, LSAPI_CB_EnvHandler fn, void * arg )
{
    struct LSAPI_key_value_pair * pEnd = pEnv + n;
    int ret;
    if ( !pEnv || !fn )
        return -1;
    while( pEnv < pEnd )
    {
        ret = (*fn)( pEnv->pKey, pEnv->keyLen,
                    pEnv->pValue, pEnv->valLen, arg );
        if ( ret <= 0 )
            return ret;
        ++pEnv;
    }
    return n;
}