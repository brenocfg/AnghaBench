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
struct LSAPI_key_value_pair {char* pKey; char* pValue; int keyLen; int valLen; } ;

/* Variables and functions */
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static int parseEnv( struct LSAPI_key_value_pair * pEnvList, int count,
            char **pBegin, char * pEnd )
{
    struct LSAPI_key_value_pair * pEnvEnd;
        int keyLen = 0, valLen = 0;
    if ( count > 8192 )
        return -1;
    pEnvEnd = pEnvList + count;
    while( pEnvList != pEnvEnd )
    {
        if ( pEnd - *pBegin < 4 )
            return -1;
        keyLen = *((unsigned char *)((*pBegin)++));
        keyLen = (keyLen << 8) + *((unsigned char *)((*pBegin)++));
        valLen = *((unsigned char *)((*pBegin)++));
        valLen = (valLen << 8) + *((unsigned char *)((*pBegin)++));
        if ( *pBegin + keyLen + valLen > pEnd )
            return -1;
        if (( !keyLen )||( !valLen ))
            return -1;

        pEnvList->pKey = *pBegin;
        *pBegin += keyLen;
        pEnvList->pValue = *pBegin;
        *pBegin += valLen;

        pEnvList->keyLen = keyLen - 1;
        pEnvList->valLen = valLen - 1;
        ++pEnvList;
    }
    if ( memcmp( *pBegin, "\0\0\0\0", 4 ) != 0 )
        return -1;
    *pBegin += 4;
    return 0;
}