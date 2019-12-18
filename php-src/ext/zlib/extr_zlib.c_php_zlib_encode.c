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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_6__ {size_t avail_in; size_t avail_out; int /*<<< orphan*/  total_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  MAX_MEM_LEVEL ; 
 int /*<<< orphan*/  PHP_ZLIB_BUFFER_SIZE_GUESS (size_t) ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflateEnd (TYPE_1__*) ; 
 int deflateInit2 (TYPE_1__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_zlib_alloc ; 
 int /*<<< orphan*/  php_zlib_free ; 
 int /*<<< orphan*/  zError (int) ; 
 int /*<<< orphan*/ * zend_string_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_truncate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string *php_zlib_encode(const char *in_buf, size_t in_len, int encoding, int level)
{
	int status;
	z_stream Z;
	zend_string *out;

	memset(&Z, 0, sizeof(z_stream));
	Z.zalloc = php_zlib_alloc;
	Z.zfree = php_zlib_free;

	if (Z_OK == (status = deflateInit2(&Z, level, Z_DEFLATED, encoding, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY))) {
		out = zend_string_alloc(PHP_ZLIB_BUFFER_SIZE_GUESS(in_len), 0);

		Z.next_in = (Bytef *) in_buf;
		Z.next_out = (Bytef *) ZSTR_VAL(out);
		Z.avail_in = in_len;
		Z.avail_out = ZSTR_LEN(out);

		status = deflate(&Z, Z_FINISH);
		deflateEnd(&Z);

		if (Z_STREAM_END == status) {
			/* size buffer down to actual length */
			out = zend_string_truncate(out, Z.total_out, 0);
			ZSTR_VAL(out)[ZSTR_LEN(out)] = '\0';
			return out;
		} else {
			zend_string_efree(out);
		}
	}

	php_error_docref(NULL, E_WARNING, "%s", zError(status));
	return NULL;
}