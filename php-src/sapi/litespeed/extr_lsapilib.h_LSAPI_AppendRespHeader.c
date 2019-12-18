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
 int LSAPI_AppendRespHeader_r (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  g_req ; 

__attribute__((used)) static inline int LSAPI_AppendRespHeader( char * pBuf, int len )
{   return LSAPI_AppendRespHeader_r( &g_req, pBuf, len );   }