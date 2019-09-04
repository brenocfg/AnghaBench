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
typedef  int /*<<< orphan*/  LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_AppendRespHeader_r (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSAPI_Finish_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LSAPI_SetRespStatus_r (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LSAPI_Write_r (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int LSAPI_ErrResponse_r( LSAPI_Request * pReq, int code, const char ** pRespHeaders,
                         const char * pBody, int bodyLen )
{
    LSAPI_SetRespStatus_r( pReq, code );
    if ( pRespHeaders )
    {
        while( *pRespHeaders )
        {
            LSAPI_AppendRespHeader_r( pReq, *pRespHeaders, strlen( *pRespHeaders ) );
            ++pRespHeaders;
        }
    }
    if ( pBody &&( bodyLen > 0 ))
    {
        LSAPI_Write_r( pReq, pBody, bodyLen );
    }
    LSAPI_Finish_r( pReq );
    return 0;
}