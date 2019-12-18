#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct lsapi_req_header {int dummy; } ;
struct lsapi_http_header_index {int dummy; } ;
struct lsapi_header_offset {int dummy; } ;
struct TYPE_11__ {char* m_pReqBuf; scalar_t__ m_specialEnvListSize; scalar_t__ m_envListSize; char* m_pScriptFile; char* m_pScriptName; char* m_pQueryString; char* m_pRequestMethod; char* m_pHttpHeader; int m_reqBodyLen; TYPE_2__* m_pHeader; struct lsapi_header_offset* m_pUnknownHeader; struct lsapi_http_header_index* m_pHeaderIndex; int /*<<< orphan*/  m_pEnvList; int /*<<< orphan*/  m_pSpecialEnvList; } ;
struct TYPE_9__ {int m_flag; } ;
struct TYPE_10__ {scalar_t__ m_cntSpecialEnv; scalar_t__ m_cntEnv; int m_scriptFileOff; int m_scriptNameOff; int m_queryStringOff; int m_requestMethodOff; int m_cntUnknownHeaders; int m_reqBodyLen; int /*<<< orphan*/  m_httpHeaderLen; TYPE_1__ m_pktHeader; } ;
typedef  TYPE_3__ LSAPI_Request ;

/* Variables and functions */
 int LSAPI_ENDIAN ; 
 int LSAPI_ENDIAN_BIT ; 
 int allocateEnvList (int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  fixEndian (TYPE_3__*) ; 
 int /*<<< orphan*/  fixHeaderIndexEndian (TYPE_3__*) ; 
 int /*<<< orphan*/  lsapi_log (char*,...) ; 
 int /*<<< orphan*/  parseContentLenFromHeader (TYPE_3__*) ; 
 int parseEnv (int /*<<< orphan*/ ,scalar_t__,char**,char*) ; 
 int validateHeaders (TYPE_3__*) ; 

__attribute__((used)) static int parseRequest( LSAPI_Request * pReq, int totalLen )
{
    int shouldFixEndian;
    char * pBegin = pReq->m_pReqBuf + sizeof( struct lsapi_req_header );
    char * pEnd = pReq->m_pReqBuf + totalLen;
    shouldFixEndian = ( LSAPI_ENDIAN != (
                pReq->m_pHeader->m_pktHeader.m_flag & LSAPI_ENDIAN_BIT ) );
    if ( shouldFixEndian )
    {
        fixEndian( pReq );
    }
    if ( (pReq->m_specialEnvListSize < pReq->m_pHeader->m_cntSpecialEnv )&&
            allocateEnvList( &pReq->m_pSpecialEnvList,
                &pReq->m_specialEnvListSize,
                pReq->m_pHeader->m_cntSpecialEnv ) == -1 )
        return -1;
    if ( (pReq->m_envListSize < pReq->m_pHeader->m_cntEnv )&&
            allocateEnvList( &pReq->m_pEnvList, &pReq->m_envListSize,
                pReq->m_pHeader->m_cntEnv ) == -1 )
        return -1;

    if ( parseEnv( pReq->m_pSpecialEnvList,
                pReq->m_pHeader->m_cntSpecialEnv,
                &pBegin, pEnd ) == -1 )
        return -1;
    if ( parseEnv( pReq->m_pEnvList, pReq->m_pHeader->m_cntEnv,
                &pBegin, pEnd ) == -1 )
        return -1;
    if (pReq->m_pHeader->m_scriptFileOff < 0
        || pReq->m_pHeader->m_scriptFileOff >= totalLen
        || pReq->m_pHeader->m_scriptNameOff < 0
        || pReq->m_pHeader->m_scriptNameOff >= totalLen
        || pReq->m_pHeader->m_queryStringOff < 0
        || pReq->m_pHeader->m_queryStringOff >= totalLen
        || pReq->m_pHeader->m_requestMethodOff < 0
        || pReq->m_pHeader->m_requestMethodOff >= totalLen)
    {
        lsapi_log("Bad request header - ERROR#1\n");
        return -1;
    }
    pReq->m_pScriptFile     = pReq->m_pReqBuf + pReq->m_pHeader->m_scriptFileOff;
    pReq->m_pScriptName     = pReq->m_pReqBuf + pReq->m_pHeader->m_scriptNameOff;
    pReq->m_pQueryString    = pReq->m_pReqBuf + pReq->m_pHeader->m_queryStringOff;
    pReq->m_pRequestMethod  = pReq->m_pReqBuf + pReq->m_pHeader->m_requestMethodOff;

    pBegin = pReq->m_pReqBuf + (( pBegin - pReq->m_pReqBuf + 7 ) & (~0x7));
    pReq->m_pHeaderIndex = ( struct lsapi_http_header_index * )pBegin;
    pBegin += sizeof( struct lsapi_http_header_index );

    pReq->m_pUnknownHeader = (struct lsapi_header_offset *)pBegin;
    pBegin += sizeof( struct lsapi_header_offset) *
                    pReq->m_pHeader->m_cntUnknownHeaders;

    pReq->m_pHttpHeader = pBegin;
    pBegin += pReq->m_pHeader->m_httpHeaderLen;
    if ( pBegin != pEnd )
    {
        lsapi_log("Request header does match total size, total: %d, "
                 "real: %ld\n", totalLen, pBegin - pReq->m_pReqBuf );
        return -1;
    }
    if ( shouldFixEndian )
    {
        fixHeaderIndexEndian( pReq );
    }

    if (validateHeaders(pReq) == -1)
    {
        lsapi_log("Bad request header - ERROR#2\n");
        return -1;
    }

    pReq->m_reqBodyLen = pReq->m_pHeader->m_reqBodyLen;
    if ( pReq->m_reqBodyLen == -2 )
    {
        parseContentLenFromHeader(pReq);
    }

    return 0;
}