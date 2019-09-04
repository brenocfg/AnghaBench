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
typedef  int /*<<< orphan*/  php_conv_qprint_encode ;
typedef  int /*<<< orphan*/  php_conv_qprint_decode ;
typedef  int /*<<< orphan*/  php_conv_base64_encode ;
typedef  int /*<<< orphan*/  php_conv_base64_decode ;
typedef  char php_conv ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  GET_BOOL_PROP (int /*<<< orphan*/  const*,int,char*) ; 
 int /*<<< orphan*/  GET_STR_PROP (int /*<<< orphan*/  const*,char*,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_UINT_PROP (int /*<<< orphan*/  const*,unsigned int,char*) ; 
#define  PHP_CONV_BASE64_DECODE 131 
#define  PHP_CONV_BASE64_ENCODE 130 
#define  PHP_CONV_QPRINT_DECODE 129 
#define  PHP_CONV_QPRINT_ENCODE 128 
 int PHP_CONV_QPRINT_OPT_BINARY ; 
 int PHP_CONV_QPRINT_OPT_FORCE_ENCODE_FIRST ; 
 int /*<<< orphan*/  pefree (char*,int) ; 
 char* pemalloc (int,int) ; 
 char* pestrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_conv_base64_decode_ctor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_conv_base64_encode_ctor (int /*<<< orphan*/ *,unsigned int,char*,size_t,int,int) ; 
 int /*<<< orphan*/  php_conv_qprint_decode_ctor (int /*<<< orphan*/ *,char*,size_t,int,int) ; 
 int /*<<< orphan*/  php_conv_qprint_encode_ctor (int /*<<< orphan*/ *,unsigned int,char*,size_t,int,int,int) ; 

__attribute__((used)) static php_conv *php_conv_open(int conv_mode, const HashTable *options, int persistent)
{
	/* FIXME: I'll have to replace this ugly code by something neat
	   (factories?) in the near future. */
	php_conv *retval = NULL;

	switch (conv_mode) {
		case PHP_CONV_BASE64_ENCODE: {
			unsigned int line_len = 0;
			char *lbchars = NULL;
			size_t lbchars_len;

			if (options != NULL) {
				GET_STR_PROP(options, lbchars, lbchars_len, "line-break-chars", 0);
				GET_UINT_PROP(options, line_len, "line-length");
				if (line_len < 4) {
					if (lbchars != NULL) {
						pefree(lbchars, 0);
					}
					lbchars = NULL;
				} else {
					if (lbchars == NULL) {
						lbchars = pestrdup("\r\n", 0);
						lbchars_len = 2;
					}
				}
			}
			retval = pemalloc(sizeof(php_conv_base64_encode), persistent);
			if (lbchars != NULL) {
				if (php_conv_base64_encode_ctor((php_conv_base64_encode *)retval, line_len, lbchars, lbchars_len, 1, persistent)) {
					if (lbchars != NULL) {
						pefree(lbchars, 0);
					}
					goto out_failure;
				}
				pefree(lbchars, 0);
			} else {
				if (php_conv_base64_encode_ctor((php_conv_base64_encode *)retval, 0, NULL, 0, 0, persistent)) {
					goto out_failure;
				}
			}
		} break;

		case PHP_CONV_BASE64_DECODE:
			retval = pemalloc(sizeof(php_conv_base64_decode), persistent);
			if (php_conv_base64_decode_ctor((php_conv_base64_decode *)retval)) {
				goto out_failure;
			}
			break;

		case PHP_CONV_QPRINT_ENCODE: {
			unsigned int line_len = 0;
			char *lbchars = NULL;
			size_t lbchars_len;
			int opts = 0;

			if (options != NULL) {
				int opt_binary = 0;
				int opt_force_encode_first = 0;

				GET_STR_PROP(options, lbchars, lbchars_len, "line-break-chars", 0);
				GET_UINT_PROP(options, line_len, "line-length");
				GET_BOOL_PROP(options, opt_binary, "binary");
				GET_BOOL_PROP(options, opt_force_encode_first, "force-encode-first");

				if (line_len < 4) {
					if (lbchars != NULL) {
						pefree(lbchars, 0);
					}
					lbchars = NULL;
				} else {
					if (lbchars == NULL) {
						lbchars = pestrdup("\r\n", 0);
						lbchars_len = 2;
					}
				}
				opts |= (opt_binary ? PHP_CONV_QPRINT_OPT_BINARY : 0);
				opts |= (opt_force_encode_first ? PHP_CONV_QPRINT_OPT_FORCE_ENCODE_FIRST : 0);
			}
			retval = pemalloc(sizeof(php_conv_qprint_encode), persistent);
			if (lbchars != NULL) {
				if (php_conv_qprint_encode_ctor((php_conv_qprint_encode *)retval, line_len, lbchars, lbchars_len, 1, opts, persistent)) {
					pefree(lbchars, 0);
					goto out_failure;
				}
				pefree(lbchars, 0);
			} else {
				if (php_conv_qprint_encode_ctor((php_conv_qprint_encode *)retval, 0, NULL, 0, 0, opts, persistent)) {
					goto out_failure;
				}
			}
		} break;

		case PHP_CONV_QPRINT_DECODE: {
			char *lbchars = NULL;
			size_t lbchars_len;

			if (options != NULL) {
				/* If line-break-chars are not specified, filter will attempt to detect line endings (\r, \n, or \r\n) */
				GET_STR_PROP(options, lbchars, lbchars_len, "line-break-chars", 0);
			}

			retval = pemalloc(sizeof(php_conv_qprint_decode), persistent);
			if (lbchars != NULL) {
				if (php_conv_qprint_decode_ctor((php_conv_qprint_decode *)retval, lbchars, lbchars_len, 1, persistent)) {
					pefree(lbchars, 0);
					goto out_failure;
				}
				pefree(lbchars, 0);
			} else {
				if (php_conv_qprint_decode_ctor((php_conv_qprint_decode *)retval, NULL, 0, 0, persistent)) {
					goto out_failure;
				}
			}
		} break;

		default:
			retval = NULL;
			break;
	}
	return retval;

out_failure:
	if (retval != NULL) {
		pefree(retval, persistent);
	}
	return NULL;
}