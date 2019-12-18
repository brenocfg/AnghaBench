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
struct TYPE_3__ {int /*<<< orphan*/ * context; int /*<<< orphan*/  old_header; } ;
typedef  TYPE_1__ sdlCtx ;

/* Variables and functions */
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_context_set_option (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

void sdl_restore_uri_credentials(sdlCtx *ctx)
{
	if (Z_TYPE(ctx->old_header) != IS_UNDEF) {
	    php_stream_context_set_option(ctx->context, "http", "header", &ctx->old_header);
	    zval_ptr_dtor(&ctx->old_header);
		ZVAL_UNDEF(&ctx->old_header);
	}
	ctx->context = NULL;
}