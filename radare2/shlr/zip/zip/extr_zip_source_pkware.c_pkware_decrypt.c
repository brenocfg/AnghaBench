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
typedef  int /*<<< orphan*/  zip_uint8_t ;
typedef  int /*<<< orphan*/  zip_uint64_t ;
typedef  int zip_int64_t ;
struct zip_stat {int valid; int /*<<< orphan*/  comp_size; int /*<<< orphan*/  encryption_method; } ;
struct zip_source {int dummy; } ;
struct trad_pkware {int /*<<< orphan*/ * e; } ;
typedef  enum zip_source_cmd { ____Placeholder_zip_source_cmd } zip_source_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  HEADERLEN ; 
 int /*<<< orphan*/  ZIP_EM_NONE ; 
 int /*<<< orphan*/  ZIP_ER_INVAL ; 
#define  ZIP_SOURCE_CLOSE 133 
#define  ZIP_SOURCE_ERROR 132 
 int ZIP_SOURCE_ERR_LOWER ; 
#define  ZIP_SOURCE_FREE 131 
#define  ZIP_SOURCE_OPEN 130 
#define  ZIP_SOURCE_READ 129 
#define  ZIP_SOURCE_STAT 128 
 int ZIP_STAT_COMP_SIZE ; 
 int ZIP_STAT_ENCRYPTION_METHOD ; 
 int /*<<< orphan*/  decrypt (struct trad_pkware*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrypt_header (struct zip_source*,struct trad_pkware*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pkware_free (struct trad_pkware*) ; 
 int zip_source_read (struct zip_source*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zip_int64_t
pkware_decrypt(struct zip_source *src, void *ud, void *data,
	       zip_uint64_t len, enum zip_source_cmd cmd)
{
    struct trad_pkware *ctx;
    zip_int64_t n;

    ctx = (struct trad_pkware *)ud;

    switch (cmd) {
    case ZIP_SOURCE_OPEN:
	if (decrypt_header(src, ctx) < 0)
	    return -1;
	return 0;

    case ZIP_SOURCE_READ:
	if ((n=zip_source_read(src, data, len)) < 0)
	    return ZIP_SOURCE_ERR_LOWER;

	decrypt((struct trad_pkware *)ud, (zip_uint8_t *)data, (zip_uint8_t *)data, (zip_uint64_t)n,
		0);
	return n;

    case ZIP_SOURCE_CLOSE:
	return 0;

    case ZIP_SOURCE_STAT:
	{
	    struct zip_stat *st;

	    st = (struct zip_stat *)data;

	    st->encryption_method = ZIP_EM_NONE;
	    st->valid |= ZIP_STAT_ENCRYPTION_METHOD;
	    /* XXX: deduce HEADERLEN from size for uncompressed */
	    if (st->valid & ZIP_STAT_COMP_SIZE)
		st->comp_size -= HEADERLEN;
	}
	return 0;

    case ZIP_SOURCE_ERROR:
	memcpy(data, ctx->e, sizeof(int)*2);
	return sizeof(int)*2;

    case ZIP_SOURCE_FREE:
	pkware_free(ctx);
	return 0;

    default:
	ctx->e[0] = ZIP_ER_INVAL;
	ctx->e[1] = 0;
	return -1;
    }
}