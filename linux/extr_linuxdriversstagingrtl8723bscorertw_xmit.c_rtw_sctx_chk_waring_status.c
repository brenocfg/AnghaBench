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
#define  RTW_SCTX_DONE_BUF_ALLOC 132 
#define  RTW_SCTX_DONE_BUF_FREE 131 
#define  RTW_SCTX_DONE_DEV_REMOVE 130 
#define  RTW_SCTX_DONE_DRV_STOP 129 
#define  RTW_SCTX_DONE_UNKNOWN 128 

__attribute__((used)) static bool rtw_sctx_chk_waring_status(int status)
{
	switch (status) {
	case RTW_SCTX_DONE_UNKNOWN:
	case RTW_SCTX_DONE_BUF_ALLOC:
	case RTW_SCTX_DONE_BUF_FREE:

	case RTW_SCTX_DONE_DRV_STOP:
	case RTW_SCTX_DONE_DEV_REMOVE:
		return true;
	default:
		return false;
	}
}