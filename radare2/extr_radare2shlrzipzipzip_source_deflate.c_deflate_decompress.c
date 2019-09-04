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
typedef  int zip_uint64_t ;
typedef  int zip_int64_t ;
typedef  int /*<<< orphan*/  uInt ;
struct zip_stat {int /*<<< orphan*/  size; int /*<<< orphan*/  comp_size; int /*<<< orphan*/  comp_method; } ;
struct zip_source {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  avail_in; int /*<<< orphan*/ * next_in; int /*<<< orphan*/ * opaque; void* zfree; void* zalloc; } ;
struct deflate {int* e; TYPE_1__ zstr; scalar_t__ buffer; } ;
typedef  enum zip_source_cmd { ____Placeholder_zip_source_cmd } zip_source_cmd ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_WBITS ; 
 int /*<<< orphan*/  ZIP_CM_STORE ; 
 int ZIP_ER_INVAL ; 
 int ZIP_ER_ZLIB ; 
#define  ZIP_SOURCE_CLOSE 133 
#define  ZIP_SOURCE_ERROR 132 
 int ZIP_SOURCE_ERR_LOWER ; 
#define  ZIP_SOURCE_FREE 131 
#define  ZIP_SOURCE_OPEN 130 
#define  ZIP_SOURCE_READ 129 
#define  ZIP_SOURCE_STAT 128 
 void* Z_NULL ; 
 int Z_OK ; 
 int decompress_read (struct zip_source*,struct deflate*,void*,int) ; 
 int /*<<< orphan*/  free (struct deflate*) ; 
 int /*<<< orphan*/  inflateEnd (TYPE_1__*) ; 
 int inflateInit2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 int zip_source_read (struct zip_source*,scalar_t__,int) ; 

__attribute__((used)) static zip_int64_t
deflate_decompress(struct zip_source *src, void *ud, void *data,
		   zip_uint64_t len, enum zip_source_cmd cmd)
{
    struct deflate *ctx;
    zip_int64_t n;
    int ret;

    ctx = (struct deflate *)ud;

    switch (cmd) {
    case ZIP_SOURCE_OPEN:
	if ((n=zip_source_read(src, ctx->buffer, sizeof(ctx->buffer))) < 0)
	    return ZIP_SOURCE_ERR_LOWER;

	ctx->zstr.zalloc = Z_NULL;
	ctx->zstr.zfree = Z_NULL;
	ctx->zstr.opaque = NULL;
	ctx->zstr.next_in = (Bytef *)ctx->buffer;
	ctx->zstr.avail_in = (uInt)n /* XXX: check for overflow */;

	/* negative value to tell zlib that there is no header */
	if ((ret=inflateInit2(&ctx->zstr, -MAX_WBITS)) != Z_OK) {
	    ctx->e[0] = ZIP_ER_ZLIB;
	    ctx->e[1] = ret;

	    return -1;
	}
	return 0;

    case ZIP_SOURCE_READ:
	return decompress_read(src, ctx, data, len);

    case ZIP_SOURCE_CLOSE:
	inflateEnd(&ctx->zstr);
	return 0;

    case ZIP_SOURCE_STAT:
	{
	    struct zip_stat *st;

	    st = (struct zip_stat *)data;

	    st->comp_method = ZIP_CM_STORE;
	    if (st->comp_size > 0 && st->size > 0)
		st->comp_size = st->size;
	}
	return 0;

    case ZIP_SOURCE_ERROR:
	if (len < sizeof(int)*2)
	    return -1;

	memcpy(data, ctx->e, sizeof(int)*2);
	return sizeof(int)*2;

    case ZIP_SOURCE_FREE:
	/* XXX: inflateEnd if close was not called */
	free(ctx);
	return 0;

    default:
	ctx->e[0] = ZIP_ER_INVAL;
	ctx->e[1] = 0;
	return -1;
    }
    
}