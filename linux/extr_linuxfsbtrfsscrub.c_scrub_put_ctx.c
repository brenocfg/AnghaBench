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
struct scrub_ctx {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scrub_free_ctx (struct scrub_ctx*) ; 

__attribute__((used)) static void scrub_put_ctx(struct scrub_ctx *sctx)
{
	if (refcount_dec_and_test(&sctx->refs))
		scrub_free_ctx(sctx);
}