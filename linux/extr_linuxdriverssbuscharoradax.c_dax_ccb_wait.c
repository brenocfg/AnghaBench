#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct dax_ctx {scalar_t__ ca_buf_ra; TYPE_1__* ca_buf; } ;
struct dax_cca {int dummy; } ;
struct TYPE_2__ {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ CCA_STAT_NOT_COMPLETED ; 
 int DAX_CCB_RETRIES ; 
 int /*<<< orphan*/  DAX_CCB_USEC ; 
 int dax_ccb_kill (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dax_dbg (char*,int,...) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dax_ccb_wait(struct dax_ctx *ctx, int idx)
{
	int ret, nretries;
	u16 kill_res;

	dax_dbg("idx=%d", idx);

	for (nretries = 0; nretries < DAX_CCB_RETRIES; nretries++) {
		if (ctx->ca_buf[idx].status == CCA_STAT_NOT_COMPLETED)
			udelay(DAX_CCB_USEC);
		else
			return;
	}
	dax_dbg("ctx (%p): CCB[%d] timed out, wait usec=%d, retries=%d. Killing ccb",
		(void *)ctx, idx, DAX_CCB_USEC, DAX_CCB_RETRIES);

	ret = dax_ccb_kill(ctx->ca_buf_ra + idx * sizeof(struct dax_cca),
			   &kill_res);
	dax_dbg("Kill CCB[%d] %s", idx, ret ? "failed" : "succeeded");
}