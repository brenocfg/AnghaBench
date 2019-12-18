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
struct gss_cl_ctx {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  gss_free_ctx (struct gss_cl_ctx*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
gss_put_ctx(struct gss_cl_ctx *ctx)
{
	if (refcount_dec_and_test(&ctx->count))
		gss_free_ctx(ctx);
}