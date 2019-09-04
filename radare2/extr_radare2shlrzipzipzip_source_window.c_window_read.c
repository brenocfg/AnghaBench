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
typedef  int zip_uint64_t ;
typedef  int zip_int64_t ;
struct zip_stat {int valid; int /*<<< orphan*/  size; } ;
struct zip_source {int dummy; } ;
struct window {int skip; int left; void** e; int /*<<< orphan*/  len; } ;
typedef  enum zip_source_cmd { ____Placeholder_zip_source_cmd } zip_source_cmd ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 void* ZIP_ER_EOF ; 
#define  ZIP_SOURCE_CLOSE 133 
#define  ZIP_SOURCE_ERROR 132 
 int ZIP_SOURCE_ERR_LOWER ; 
#define  ZIP_SOURCE_FREE 131 
#define  ZIP_SOURCE_OPEN 130 
#define  ZIP_SOURCE_READ 129 
#define  ZIP_SOURCE_STAT 128 
 int ZIP_STAT_COMP_SIZE ; 
 int ZIP_STAT_CRC ; 
 int ZIP_STAT_SIZE ; 
 int /*<<< orphan*/  free (struct window*) ; 
 int /*<<< orphan*/  memcpy (void*,void**,int) ; 
 int zip_source_read (struct zip_source*,void*,int) ; 

__attribute__((used)) static zip_int64_t
window_read(struct zip_source *src, void *_ctx, void *data,
	    zip_uint64_t len, enum zip_source_cmd cmd)
{
    struct window *ctx;
    zip_int64_t ret;
    zip_uint64_t n, i;
    char b[8192];

    ctx = (struct window *)_ctx;

    switch (cmd) {
    case ZIP_SOURCE_OPEN:
	for (n=0; n<ctx->skip; n+=(zip_uint64_t)ret) {
	    i = (ctx->skip-n > sizeof(b) ? sizeof(b) : ctx->skip-n);
	    if ((ret=zip_source_read(src, b, i)) < 0)
		return ZIP_SOURCE_ERR_LOWER;
	    if (ret==0) {
		ctx->e[0] = ZIP_ER_EOF;
		ctx->e[1] = 0;
		return -1;
	    }
	}
	return 0;

    case ZIP_SOURCE_READ:
	if (len > ctx->left)
	    len = ctx->left;
	
	if (len == 0)
	    return 0;

	if ((ret=zip_source_read(src, data, len)) < 0)
	    return ZIP_SOURCE_ERR_LOWER;

	ctx->left -= (zip_uint64_t)ret;

        if (ret == 0) {
	    if (ctx->left > 0) {
		ctx->e[0] = ZIP_ER_EOF;
		ctx->e[1] = 0;
		return -1;
	    }
	}
	return ret;

    case ZIP_SOURCE_CLOSE:
	return 0;

    case ZIP_SOURCE_STAT:
	{
	    struct zip_stat *st;

	    st = (struct zip_stat *)data;

	    st->size = ctx->len;
	    st->valid |= ZIP_STAT_SIZE;
	    st->valid &= ~(ZIP_STAT_CRC|ZIP_STAT_COMP_SIZE);
	}
	return 0;
	
    case ZIP_SOURCE_ERROR:
	memcpy(data, ctx->e, sizeof(ctx->e));
	return 0;

    case ZIP_SOURCE_FREE:
	free(ctx);
	return 0;

    default:
	return -1;
    }
    
}