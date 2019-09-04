#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* data; } ;
struct TYPE_5__ {TYPE_1__ buffer; } ;
typedef  TYPE_2__ php_zlib_context ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_2__*) ; 

__attribute__((used)) static void php_zlib_output_handler_context_dtor(void *opaq)
{
	php_zlib_context *ctx = (php_zlib_context *) opaq;

	if (ctx) {
		if (ctx->buffer.data) {
			efree(ctx->buffer.data);
		}
		efree(ctx);
	}
}