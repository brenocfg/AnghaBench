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
struct TYPE_7__ {char* m_pHttpHeader; TYPE_2__* m_pHeader; struct lsapi_header_offset* m_pUnknownHeader; TYPE_1__* m_pHeaderIndex; } ;
struct TYPE_6__ {scalar_t__ m_cntUnknownHeaders; } ;
struct TYPE_5__ {int* m_headerOff; int* m_headerLen; } ;
typedef  TYPE_3__ LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/ * CGI_HEADERS ; 
 int H_TRANSFER_ENCODING ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 char toupper (char) ; 

__attribute__((used)) static char * GetHeaderVar( LSAPI_Request * pReq, const char * name )
{
    int i;
    char * pValue;
    for( i = 0; i < H_TRANSFER_ENCODING; ++i )
    {
        if ( pReq->m_pHeaderIndex->m_headerOff[i] )
        {
            if ( strcmp( name, CGI_HEADERS[i] ) == 0 )
            {
                pValue = pReq->m_pHttpHeader
                         + pReq->m_pHeaderIndex->m_headerOff[i];
                if ( *(pValue + pReq->m_pHeaderIndex->m_headerLen[i]) != '\0')
                {
                    *(pValue + pReq->m_pHeaderIndex->m_headerLen[i]) = '\0';
                }
                return pValue;
            }
        }
    }
    if ( pReq->m_pHeader->m_cntUnknownHeaders > 0 )
    {
        const char *p;
        char *pKey;
        char *pKeyEnd;
        int  keyLen;
        struct lsapi_header_offset * pCur, *pEnd;
        pCur = pReq->m_pUnknownHeader;
        pEnd = pCur + pReq->m_pHeader->m_cntUnknownHeaders;
        while( pCur < pEnd )
        {
            pKey = pReq->m_pHttpHeader + pCur->nameOff;
            keyLen = pCur->nameLen;
            pKeyEnd = pKey + keyLen;
            p = &name[5];

            while(( pKey < pKeyEnd )&&( *p ))
            {
                char ch = toupper( *pKey );
                if ((ch != *p )||(( *p == '_' )&&( ch != '-')))
                    break;
                ++p; ++pKey;
            }
            if (( pKey == pKeyEnd )&& (!*p ))
            {
                pValue = pReq->m_pHttpHeader + pCur->valueOff;

                if ( *(pValue + pCur->valueLen) != '\0')
                {
                    *(pValue + pCur->valueLen) = '\0';
                }
                return pValue;
            }
            ++pCur;
        }
    }
    return NULL;
}