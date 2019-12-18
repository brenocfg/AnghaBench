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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_2__ {int /*<<< orphan*/  mdc_ctx; scalar_t__ in_mdc_pkt; scalar_t__ use_mdcbuf_filter; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int PXE_PGP_CORRUPT_DATA ; 
 int pullf_read (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  px_debug (char*) ; 
 int /*<<< orphan*/  px_md_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
mdc_read(void *priv, PullFilter *src, int len,
		 uint8 **data_p, uint8 *buf, int buflen)
{
	int			res;
	PGP_Context *ctx = priv;

	/* skip this filter? */
	if (ctx->use_mdcbuf_filter || ctx->in_mdc_pkt)
		return pullf_read(src, len, data_p);

	res = pullf_read(src, len, data_p);
	if (res < 0)
		return res;
	if (res == 0)
	{
		px_debug("mdc_read: unexpected eof");
		return PXE_PGP_CORRUPT_DATA;
	}
	px_md_update(ctx->mdc_ctx, *data_p, res);

	return res;
}