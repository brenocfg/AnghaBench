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
struct _headerInfo {char* _name; int _nameLen; char* _value; int _valueLen; } ;
struct TYPE_7__ {char* m_pHttpHeader; TYPE_2__* m_pHeader; struct lsapi_header_offset* m_pUnknownHeader; TYPE_1__* m_pHeaderIndex; } ;
struct TYPE_6__ {scalar_t__ m_cntUnknownHeaders; } ;
struct TYPE_5__ {int* m_headerOff; int* m_headerLen; } ;
typedef  TYPE_3__ LSAPI_Request ;
typedef  int (* LSAPI_CB_EnvHandler ) (char*,int,char*,int,void*) ;

/* Variables and functions */
 char** HTTP_HEADERS ; 
 int* HTTP_HEADER_LEN ; 
 int H_TRANSFER_ENCODING ; 
 int /*<<< orphan*/  compareValueLocation ; 
 int /*<<< orphan*/  qsort (struct _headerInfo*,int,int,int /*<<< orphan*/ ) ; 
 int stub1 (char*,int,char*,int,void*) ; 

int LSAPI_ForeachOrgHeader_r( LSAPI_Request * pReq,
            LSAPI_CB_EnvHandler fn, void * arg )
{
    int i;
    int len = 0;
    char * pValue;
    int ret;
    int count = 0;
    struct _headerInfo headers[512];

    if ( !pReq || !fn )
        return -1;

    if ( !pReq->m_pHeaderIndex )
        return 0;

    for( i = 0; i < H_TRANSFER_ENCODING; ++i )
    {
        if ( pReq->m_pHeaderIndex->m_headerOff[i] )
        {
            len = pReq->m_pHeaderIndex->m_headerLen[i];
            pValue = pReq->m_pHttpHeader + pReq->m_pHeaderIndex->m_headerOff[i];
            *(pValue + len ) = 0;
            headers[count]._name = HTTP_HEADERS[i];
            headers[count]._nameLen = HTTP_HEADER_LEN[i];
            headers[count]._value = pValue;
            headers[count]._valueLen = len;
            ++count;

            //ret = (*fn)( HTTP_HEADERS[i], HTTP_HEADER_LEN[i],
            //            pValue, len, arg );
            //if ( ret <= 0 )
            //    return ret;
        }
    }
    if ( pReq->m_pHeader->m_cntUnknownHeaders > 0 )
    {
        char *pKey;
        int  keyLen;
        struct lsapi_header_offset * pCur, *pEnd;
        pCur = pReq->m_pUnknownHeader;
        pEnd = pCur + pReq->m_pHeader->m_cntUnknownHeaders;
        while( pCur < pEnd )
        {
            pKey = pReq->m_pHttpHeader + pCur->nameOff;
            keyLen = pCur->nameLen;
            *(pKey + keyLen ) = 0;

            pValue = pReq->m_pHttpHeader + pCur->valueOff;
            *(pValue + pCur->valueLen ) = 0;
            headers[count]._name = pKey;
            headers[count]._nameLen = keyLen;
            headers[count]._value = pValue;
            headers[count]._valueLen = pCur->valueLen;
            ++count;
            if ( count == 512 )
                break;
            //ret = (*fn)( pKey, keyLen,
            //            pValue, pCur->valueLen, arg );
            //if ( ret <= 0 )
            //    return ret;
            ++pCur;
        }
    }
    qsort( headers, count, sizeof( struct _headerInfo ), compareValueLocation );
    for( i = 0; i < count; ++i )
    {
        ret = (*fn)( headers[i]._name, headers[i]._nameLen,
                    headers[i]._value, headers[i]._valueLen, arg );
        if ( ret <= 0 )
            return ret;
    }
    return count;
}