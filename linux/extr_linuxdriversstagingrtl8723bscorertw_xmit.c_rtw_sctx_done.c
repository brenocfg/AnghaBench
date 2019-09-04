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
struct submit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_SCTX_DONE_SUCCESS ; 
 int /*<<< orphan*/  rtw_sctx_done_err (struct submit_ctx**,int /*<<< orphan*/ ) ; 

void rtw_sctx_done(struct submit_ctx **sctx)
{
	rtw_sctx_done_err(sctx, RTW_SCTX_DONE_SUCCESS);
}