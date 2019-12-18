#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  m_reqBodyLen; } ;
typedef  TYPE_1__ LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  H_CONTENT_LENGTH ; 
 char* LSAPI_GetHeader_r (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoll (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parseContentLenFromHeader(LSAPI_Request * pReq)
{
    const char * pContentLen = LSAPI_GetHeader_r( pReq, H_CONTENT_LENGTH );
    if ( pContentLen )
        pReq->m_reqBodyLen = strtoll( pContentLen, NULL, 10 );
    return 0;
}