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
struct TYPE_3__ {int m_fdListen; } ;
typedef  TYPE_1__ LSAPI_Request ;

/* Variables and functions */

int LSAPI_Is_Listen_r( LSAPI_Request * pReq)
{
    return pReq->m_fdListen != -1;
}