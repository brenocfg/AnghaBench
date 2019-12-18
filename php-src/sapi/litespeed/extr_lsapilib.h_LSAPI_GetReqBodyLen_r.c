#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
struct TYPE_3__ {int m_reqBodyLen; } ;
typedef  TYPE_1__ LSAPI_Request ;

/* Variables and functions */

__attribute__((used)) static inline off_t LSAPI_GetReqBodyLen_r( LSAPI_Request * pReq )
{
    if ( pReq )
        return pReq->m_reqBodyLen;
    return -1;
}