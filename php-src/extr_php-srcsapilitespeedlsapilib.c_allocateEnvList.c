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
struct LSAPI_key_value_pair {int dummy; } ;

/* Variables and functions */
 scalar_t__ realloc (struct LSAPI_key_value_pair*,int) ; 

__attribute__((used)) static int allocateEnvList( struct LSAPI_key_value_pair ** pEnvList,
                        int *curSize, int newSize )
{
    struct LSAPI_key_value_pair * pBuf;
    if ( *curSize >= newSize )
        return 0;
    if ( newSize > 8192 )
        return -1;
    pBuf = (struct LSAPI_key_value_pair *)realloc( *pEnvList, newSize *
                    sizeof(struct LSAPI_key_value_pair) );
    if ( pBuf )
    {
        *pEnvList = pBuf;
        *curSize  = newSize;
        return 0;
    }
    else
        return -1;

}