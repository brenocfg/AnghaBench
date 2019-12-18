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
struct MDCBufData {TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mdc_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  px_free (struct MDCBufData*) ; 
 int /*<<< orphan*/  px_md_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_memset (struct MDCBufData*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mdcbuf_free(void *priv)
{
	struct MDCBufData *st = priv;

	px_md_free(st->ctx->mdc_ctx);
	st->ctx->mdc_ctx = NULL;
	px_memset(st, 0, sizeof(*st));
	px_free(st);
}