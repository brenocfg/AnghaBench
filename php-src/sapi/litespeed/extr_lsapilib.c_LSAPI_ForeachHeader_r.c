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
typedef  int (* LSAPI_CB_EnvHandler ) (char*,int,char*,int,void*) ;

/* Variables and functions */
 char** CGI_HEADERS ; 
 int* CGI_HEADER_LEN ; 
 int H_TRANSFER_ENCODING ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int stub1 (char*,int,char*,int,void*) ; 
 int stub2 (char*,int,char*,int,void*) ; 
 int /*<<< orphan*/  toupper (char) ; 

int LSAPI_ForeachHeader_r( LSAPI_Request * pReq,
            LSAPI_CB_EnvHandler fn, void * arg )
{
    int i;
    int len = 0;
    char * pValue;
    int ret;
    int count = 0;
    if ( !pReq || !fn )
        return -1;
    for( i = 0; i < H_TRANSFER_ENCODING; ++i )
    {
        if ( pReq->m_pHeaderIndex->m_headerOff[i] )
        {
            len = pReq->m_pHeaderIndex->m_headerLen[i];
            pValue = pReq->m_pHttpHeader + pReq->m_pHeaderIndex->m_headerOff[i];
            *(pValue + len ) = 0;
            ret = (*fn)( CGI_HEADERS[i], CGI_HEADER_LEN[i],
                        pValue, len, arg );
            ++count;
            if ( ret <= 0 )
                return ret;
        }
    }
    if ( pReq->m_pHeader->m_cntUnknownHeaders > 0 )
    {
        char achHeaderName[256];
        char *p;
        char *pKey;
        char *pKeyEnd ;
        int  keyLen;
        struct lsapi_header_offset * pCur, *pEnd;
        pCur = pReq->m_pUnknownHeader;
        pEnd = pCur + pReq->m_pHeader->m_cntUnknownHeaders;
        while( pCur < pEnd )
        {
            pKey = pReq->m_pHttpHeader + pCur->nameOff;
            keyLen = pCur->nameLen;
            if ( keyLen > 250 )
                keyLen = 250;
            pKeyEnd = pKey + keyLen;
            memcpy( achHeaderName, "HTTP_", 5 );
            p = &achHeaderName[5];

            while( pKey < pKeyEnd )
            {
                char ch = *pKey++;
                if ( ch == '-' )
                    *p++ = '_';
                else
                    *p++ = toupper( ch );
            }
            *p = 0;
            keyLen += 5;

            pValue = pReq->m_pHttpHeader + pCur->valueOff;
            *(pValue + pCur->valueLen ) = 0;
            ret = (*fn)( achHeaderName, keyLen,
                        pValue, pCur->valueLen, arg );
            if ( ret <= 0 )
                return ret;
            ++pCur;
        }
    }
    return count + pReq->m_pHeader->m_cntUnknownHeaders;
}