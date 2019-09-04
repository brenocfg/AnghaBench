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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_ReadReqBody_r (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  g_req ; 

__attribute__((used)) static inline ssize_t LSAPI_ReadReqBody( char * pBuf, size_t len )
{   return LSAPI_ReadReqBody_r( &g_req, pBuf, len );        }