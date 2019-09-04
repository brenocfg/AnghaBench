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
typedef  int /*<<< orphan*/  zip_uint64_t ;
typedef  int zip_int64_t ;
struct zip_stat {int /*<<< orphan*/  valid; int /*<<< orphan*/  comp_size; int /*<<< orphan*/  comp_method; } ;
struct zip_source {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * next_out; int /*<<< orphan*/  avail_out; int /*<<< orphan*/ * next_in; int /*<<< orphan*/  avail_in; int /*<<< orphan*/ * opaque; void* zfree; void* zalloc; } ;
struct deflate {int* e; int /*<<< orphan*/  size; int /*<<< orphan*/  eof; TYPE_1__ zstr; int /*<<< orphan*/  mem_level; } ;
typedef  enum zip_source_cmd { ____Placeholder_zip_source_cmd } zip_source_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_WBITS ; 
 int /*<<< orphan*/  ZIP_CM_DEFLATE ; 
 int ZIP_ER_INVAL ; 
 int ZIP_ER_ZLIB ; 
#define  ZIP_SOURCE_CLOSE 133 
#define  ZIP_SOURCE_ERROR 132 
#define  ZIP_SOURCE_FREE 131 
#define  ZIP_SOURCE_OPEN 130 
#define  ZIP_SOURCE_READ 129 
#define  ZIP_SOURCE_STAT 128 
 int /*<<< orphan*/  ZIP_STAT_COMP_METHOD ; 
 int /*<<< orphan*/  ZIP_STAT_COMP_SIZE ; 
 int /*<<< orphan*/  Z_BEST_COMPRESSION ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 void* Z_NULL ; 
 int Z_OK ; 
 int compress_read (struct zip_source*,struct deflate*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflateEnd (TYPE_1__*) ; 
 int deflateInit2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflate_free (struct deflate*) ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 

__attribute__((used)) static zip_int64_t
deflate_compress(struct zip_source *src, void *ud, void *data,
		 zip_uint64_t len, enum zip_source_cmd cmd)
{
    struct deflate *ctx;
    int ret;

    ctx = (struct deflate *)ud;

    switch (cmd) {
    case ZIP_SOURCE_OPEN:
	ctx->zstr.zalloc = Z_NULL;
	ctx->zstr.zfree = Z_NULL;
	ctx->zstr.opaque = NULL;
	ctx->zstr.avail_in = 0;
	ctx->zstr.next_in = NULL;
	ctx->zstr.avail_out = 0;
	ctx->zstr.next_out = NULL;

	/* negative value to tell zlib not to write a header */
	if ((ret=deflateInit2(&ctx->zstr, Z_BEST_COMPRESSION, Z_DEFLATED,
			      -MAX_WBITS, ctx->mem_level,
			      Z_DEFAULT_STRATEGY)) != Z_OK) {
	    ctx->e[0] = ZIP_ER_ZLIB;
	    ctx->e[1] = ret;
	    return -1;
	}

	return 0;

    case ZIP_SOURCE_READ:
	return compress_read(src, ctx, data, len);

    case ZIP_SOURCE_CLOSE:
	deflateEnd(&ctx->zstr);
	return 0;

    case ZIP_SOURCE_STAT:
    	{
	    struct zip_stat *st;

	    st = (struct zip_stat *)data;

	    st->comp_method = ZIP_CM_DEFLATE;
	    st->valid |= ZIP_STAT_COMP_METHOD;
	    if (ctx->eof) {
		st->comp_size = ctx->size;
		st->valid |= ZIP_STAT_COMP_SIZE;
	    }
	    else
		st->valid &= ~ZIP_STAT_COMP_SIZE;
	}
	return 0;

    case ZIP_SOURCE_ERROR:
	memcpy(data, ctx->e, sizeof(int)*2);
	return sizeof(int)*2;

    case ZIP_SOURCE_FREE:
	deflate_free(ctx);
	return 0;

    default:
	ctx->e[0] = ZIP_ER_INVAL;
	ctx->e[1] = 0;
	return -1;
    }
}