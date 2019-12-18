#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t avail_in; int /*<<< orphan*/ * next_in; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int PHP_ZLIB_ENCODING_ANY ; 
 int PHP_ZLIB_ENCODING_RAW ; 
 int SUCCESS ; 
#define  Z_DATA_ERROR 129 
 int Z_OK ; 
#define  Z_STREAM_END 128 
 int /*<<< orphan*/  inflateEnd (TYPE_1__*) ; 
 int inflateInit2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_zlib_alloc ; 
 int /*<<< orphan*/  php_zlib_free ; 
 int php_zlib_inflate_rounds (TYPE_1__*,size_t,char**,size_t*) ; 
 int /*<<< orphan*/  zError (int) ; 

__attribute__((used)) static int php_zlib_decode(const char *in_buf, size_t in_len, char **out_buf, size_t *out_len, int encoding, size_t max_len)
{
	int status = Z_DATA_ERROR;
	z_stream Z;

	memset(&Z, 0, sizeof(z_stream));
	Z.zalloc = php_zlib_alloc;
	Z.zfree = php_zlib_free;

	if (in_len) {
retry_raw_inflate:
		status = inflateInit2(&Z, encoding);
		if (Z_OK == status) {
			Z.next_in = (Bytef *) in_buf;
			Z.avail_in = in_len + 1; /* NOTE: data must be zero terminated */

			switch (status = php_zlib_inflate_rounds(&Z, max_len, out_buf, out_len)) {
				case Z_STREAM_END:
					inflateEnd(&Z);
					return SUCCESS;

				case Z_DATA_ERROR:
					/* raw deflated data? */
					if (PHP_ZLIB_ENCODING_ANY == encoding) {
						inflateEnd(&Z);
						encoding = PHP_ZLIB_ENCODING_RAW;
						goto retry_raw_inflate;
					}
			}
			inflateEnd(&Z);
		}
	}

	*out_buf = NULL;
	*out_len = 0;

	php_error_docref(NULL, E_WARNING, "%s", zError(status));
	return FAILURE;
}