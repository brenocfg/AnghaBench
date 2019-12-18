#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  tmpbuf ;
struct TYPE_3__ {int in_mdc_pkt; int mdc_checked; int /*<<< orphan*/  mdc_ctx; scalar_t__ use_mdcbuf_filter; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int PXE_BUG ; 
 int PXE_PGP_CORRUPT_DATA ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pullf_read_max (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_debug (char*,...) ; 
 int /*<<< orphan*/  px_md_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mdc_finish(PGP_Context *ctx, PullFilter *src, int len)
{
	int			res;
	uint8		hash[20];
	uint8		tmpbuf[20];
	uint8	   *data;

	/* should not happen */
	if (ctx->use_mdcbuf_filter)
		return PXE_BUG;

	/* It's SHA1 */
	if (len != 20)
		return PXE_PGP_CORRUPT_DATA;

	/* mdc_read should not call px_md_update */
	ctx->in_mdc_pkt = 1;

	/* read data */
	res = pullf_read_max(src, len, &data, tmpbuf);
	if (res < 0)
		return res;
	if (res == 0)
	{
		px_debug("no mdc");
		return PXE_PGP_CORRUPT_DATA;
	}

	/* is the packet sane? */
	if (res != 20)
	{
		px_debug("mdc_finish: read failed, res=%d", res);
		return PXE_PGP_CORRUPT_DATA;
	}

	/*
	 * ok, we got the hash, now check
	 */
	px_md_finish(ctx->mdc_ctx, hash);
	res = memcmp(hash, data, 20);
	px_memset(hash, 0, 20);
	px_memset(tmpbuf, 0, sizeof(tmpbuf));
	if (res != 0)
	{
		px_debug("mdc_finish: mdc failed");
		return PXE_PGP_CORRUPT_DATA;
	}
	ctx->mdc_checked = 1;
	return 0;
}