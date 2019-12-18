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
struct MDCBufData {int avail; TYPE_1__* ctx; int /*<<< orphan*/ * pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdc_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  px_md_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
mdcbuf_load_data(struct MDCBufData *st, uint8 *src, int len)
{
	uint8	   *dst = st->pos + st->avail;

	memcpy(dst, src, len);
	px_md_update(st->ctx->mdc_ctx, src, len);
	st->avail += len;
}