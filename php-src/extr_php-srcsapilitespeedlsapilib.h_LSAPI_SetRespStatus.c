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
 int LSAPI_SetRespStatus_r (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_req ; 

__attribute__((used)) static inline int LSAPI_SetRespStatus( int code )
{   return LSAPI_SetRespStatus_r( &g_req, code );           }