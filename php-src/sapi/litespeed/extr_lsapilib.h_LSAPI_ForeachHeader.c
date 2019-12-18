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
typedef  int /*<<< orphan*/  LSAPI_CB_EnvHandler ;

/* Variables and functions */
 int LSAPI_ForeachHeader_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  g_req ; 

__attribute__((used)) static inline int LSAPI_ForeachHeader( LSAPI_CB_EnvHandler fn, void * arg )
{   return LSAPI_ForeachHeader_r( &g_req, fn, arg );        }