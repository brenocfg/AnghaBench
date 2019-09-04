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
struct gdIOCtx {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  efree (struct gdIOCtx*) ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _php_image_stream_ctxfreeandclose(struct gdIOCtx *ctx) /* {{{ */
{

	if(ctx->data) {
		php_stream_close((php_stream *) ctx->data);
		ctx->data = NULL;
	}
	if(ctx) {
		efree(ctx);
	}
}