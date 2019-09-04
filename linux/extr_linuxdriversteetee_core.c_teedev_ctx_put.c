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
struct tee_context {int /*<<< orphan*/  refcount; scalar_t__ releasing; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teedev_ctx_release ; 

void teedev_ctx_put(struct tee_context *ctx)
{
	if (ctx->releasing)
		return;

	kref_put(&ctx->refcount, teedev_ctx_release);
}