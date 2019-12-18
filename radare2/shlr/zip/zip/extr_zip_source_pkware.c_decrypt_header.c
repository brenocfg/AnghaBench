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
typedef  unsigned short zip_uint8_t ;
typedef  int zip_int64_t ;
struct zip_stat {unsigned short crc; int /*<<< orphan*/  mtime; } ;
struct zip_source {int dummy; } ;
struct trad_pkware {scalar_t__* e; } ;

/* Variables and functions */
 int HEADERLEN ; 
 scalar_t__ ZIP_ER_EOF ; 
 scalar_t__ ZIP_ER_WRONGPASSWD ; 
 int /*<<< orphan*/  _zip_u2d_time (int /*<<< orphan*/ ,unsigned short*,unsigned short*) ; 
 int /*<<< orphan*/  decrypt (struct trad_pkware*,unsigned short*,unsigned short*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_source_error (struct zip_source*,scalar_t__*,scalar_t__*) ; 
 int zip_source_read (struct zip_source*,unsigned short*,int) ; 
 scalar_t__ zip_source_stat (struct zip_source*,struct zip_stat*) ; 

__attribute__((used)) static int
decrypt_header(struct zip_source *src, struct trad_pkware *ctx)
{
    zip_uint8_t header[HEADERLEN];
    struct zip_stat st;
    zip_int64_t n;
    unsigned short dostime, dosdate;

    if ((n=zip_source_read(src, header, HEADERLEN)) < 0) {
	zip_source_error(src, ctx->e, ctx->e+1);
	return -1;
    }
    
    if (n != HEADERLEN) {
	ctx->e[0] = ZIP_ER_EOF;
	ctx->e[1] = 0;
	return -1;
    }

    decrypt(ctx, header, header, HEADERLEN, 0);

    if (zip_source_stat(src, &st) < 0) {
	/* stat failed, skip password validation */
	return 0;
    }

    _zip_u2d_time(st.mtime, &dostime, &dosdate);

    if (header[HEADERLEN-1] != st.crc>>24
	&& header[HEADERLEN-1] != dostime>>8) {
	ctx->e[0] = ZIP_ER_WRONGPASSWD;
	ctx->e[1] = 0;
	return -1;
    }

    return 0;
}