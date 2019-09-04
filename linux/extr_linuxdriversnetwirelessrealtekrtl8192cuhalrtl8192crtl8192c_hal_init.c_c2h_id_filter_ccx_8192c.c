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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ C2H_CCX_TX_RPT ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _TRUE ; 

s32 c2h_id_filter_ccx_8192c(u8 id)
{
	s32 ret = _FALSE;
	if (id == C2H_CCX_TX_RPT)
		ret = _TRUE;
	
	return ret;
}