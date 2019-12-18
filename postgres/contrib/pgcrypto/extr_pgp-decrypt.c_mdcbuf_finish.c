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
struct MDCBufData {int eof; int* mdc_buf; TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdc_ctx; } ;

/* Variables and functions */
 int PXE_PGP_CORRUPT_DATA ; 
 int memcmp (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  px_debug (char*) ; 
 int /*<<< orphan*/  px_md_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_md_update (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  px_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mdcbuf_finish(struct MDCBufData *st)
{
	uint8		hash[20];
	int			res;

	st->eof = 1;

	if (st->mdc_buf[0] != 0xD3 || st->mdc_buf[1] != 0x14)
	{
		px_debug("mdcbuf_finish: bad MDC pkt hdr");
		return PXE_PGP_CORRUPT_DATA;
	}
	px_md_update(st->ctx->mdc_ctx, st->mdc_buf, 2);
	px_md_finish(st->ctx->mdc_ctx, hash);
	res = memcmp(hash, st->mdc_buf + 2, 20);
	px_memset(hash, 0, 20);
	if (res)
	{
		px_debug("mdcbuf_finish: MDC does not match");
		res = PXE_PGP_CORRUPT_DATA;
	}
	return res;
}