#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ avail_in; scalar_t__ avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; } ;
struct TYPE_12__ {scalar_t__ used; scalar_t__ free; scalar_t__ aptr; scalar_t__ data; } ;
struct TYPE_14__ {TYPE_8__ Z; TYPE_2__ buffer; } ;
typedef  TYPE_4__ php_zlib_context ;
struct TYPE_13__ {int free; scalar_t__ size; scalar_t__ used; scalar_t__ data; } ;
struct TYPE_11__ {scalar_t__ used; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {int op; TYPE_3__ out; TYPE_1__ in; } ;
typedef  TYPE_5__ php_output_context ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  MAX_MEM_LEVEL ; 
 int PHP_OUTPUT_HANDLER_CLEAN ; 
 int PHP_OUTPUT_HANDLER_FINAL ; 
 int PHP_OUTPUT_HANDLER_FLUSH ; 
 int PHP_OUTPUT_HANDLER_START ; 
 scalar_t__ PHP_ZLIB_BUFFER_SIZE_GUESS (scalar_t__) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZLIBG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 int Z_FINISH ; 
 int Z_FULL_FLUSH ; 
#define  Z_OK 129 
#define  Z_STREAM_END 128 
 int Z_SYNC_FLUSH ; 
 int /*<<< orphan*/  compression_coding ; 
 int deflate (TYPE_8__*,int) ; 
 int /*<<< orphan*/  deflateEnd (TYPE_8__*) ; 
 scalar_t__ deflateInit2 (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ emalloc (scalar_t__) ; 
 scalar_t__ erealloc_recoverable (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  output_compression_level ; 

__attribute__((used)) static int php_zlib_output_handler_ex(php_zlib_context *ctx, php_output_context *output_context)
{
	int flags = Z_SYNC_FLUSH;

	if (output_context->op & PHP_OUTPUT_HANDLER_START) {
		/* start up */
		if (Z_OK != deflateInit2(&ctx->Z, ZLIBG(output_compression_level), Z_DEFLATED, ZLIBG(compression_coding), MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY)) {
			return FAILURE;
		}
	}

	if (output_context->op & PHP_OUTPUT_HANDLER_CLEAN) {
		/* free buffers */
		deflateEnd(&ctx->Z);

		if (output_context->op & PHP_OUTPUT_HANDLER_FINAL) {
			/* discard */
			return SUCCESS;
		} else {
			/* restart */
			if (Z_OK != deflateInit2(&ctx->Z, ZLIBG(output_compression_level), Z_DEFLATED, ZLIBG(compression_coding), MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY)) {
				return FAILURE;
			}
			ctx->buffer.used = 0;
		}
	} else {
		if (output_context->in.used) {
			/* append input */
			if (ctx->buffer.free < output_context->in.used) {
				if (!(ctx->buffer.aptr = erealloc_recoverable(ctx->buffer.data, ctx->buffer.used + ctx->buffer.free + output_context->in.used))) {
					deflateEnd(&ctx->Z);
					return FAILURE;
				}
				ctx->buffer.data = ctx->buffer.aptr;
				ctx->buffer.free += output_context->in.used;
			}
			memcpy(ctx->buffer.data + ctx->buffer.used, output_context->in.data, output_context->in.used);
			ctx->buffer.free -= output_context->in.used;
			ctx->buffer.used += output_context->in.used;
		}
		output_context->out.size = PHP_ZLIB_BUFFER_SIZE_GUESS(output_context->in.used);
		output_context->out.data = emalloc(output_context->out.size);
		output_context->out.free = 1;
		output_context->out.used = 0;

		ctx->Z.avail_in = ctx->buffer.used;
		ctx->Z.next_in = (Bytef *) ctx->buffer.data;
		ctx->Z.avail_out = output_context->out.size;
		ctx->Z.next_out = (Bytef *) output_context->out.data;

		if (output_context->op & PHP_OUTPUT_HANDLER_FINAL) {
			flags = Z_FINISH;
		} else if (output_context->op & PHP_OUTPUT_HANDLER_FLUSH) {
			flags = Z_FULL_FLUSH;
		}

		switch (deflate(&ctx->Z, flags)) {
			case Z_OK:
				if (flags == Z_FINISH) {
					deflateEnd(&ctx->Z);
					return FAILURE;
				}
			case Z_STREAM_END:
				if (ctx->Z.avail_in) {
					memmove(ctx->buffer.data, ctx->buffer.data + ctx->buffer.used - ctx->Z.avail_in, ctx->Z.avail_in);
				}
				ctx->buffer.free += ctx->buffer.used - ctx->Z.avail_in;
				ctx->buffer.used = ctx->Z.avail_in;
				output_context->out.used = output_context->out.size - ctx->Z.avail_out;
				break;
			default:
				deflateEnd(&ctx->Z);
				return FAILURE;
		}

		if (output_context->op & PHP_OUTPUT_HANDLER_FINAL) {
			deflateEnd(&ctx->Z);
		}
	}

	return SUCCESS;
}