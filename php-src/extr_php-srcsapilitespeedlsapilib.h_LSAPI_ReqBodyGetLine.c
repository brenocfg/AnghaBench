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

/* Variables and functions */
 int LSAPI_ReqBodyGetLine_r (int /*<<< orphan*/ *,char*,int,int*) ; 
 int /*<<< orphan*/  g_req ; 

__attribute__((used)) static inline int LSAPI_ReqBodyGetLine( char * pBuf, int len, int *getLF )
{   return LSAPI_ReqBodyGetLine_r( &g_req, pBuf, len, getLF );        }