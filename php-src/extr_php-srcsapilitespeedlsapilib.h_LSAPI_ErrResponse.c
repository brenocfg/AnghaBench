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
 int LSAPI_ErrResponse_r (int /*<<< orphan*/ *,int,char const**,char const*,int) ; 
 int /*<<< orphan*/  g_req ; 

__attribute__((used)) static inline int LSAPI_ErrResponse( int code, const char ** pRespHeaders, const char * pBody, int bodyLen )
{   return LSAPI_ErrResponse_r( &g_req, code, pRespHeaders, pBody, bodyLen );   }