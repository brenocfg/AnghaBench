#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ php_zlib_context ;
struct TYPE_7__ {int op; } ;
typedef  TYPE_2__ php_output_context ;

/* Variables and functions */
 int FAILURE ; 
 int PHP_OUTPUT_HANDLER_CLEAN ; 
 int PHP_OUTPUT_HANDLER_FINAL ; 
 int /*<<< orphan*/  PHP_OUTPUT_HANDLER_HOOK_GET_FLAGS ; 
 int /*<<< orphan*/  PHP_OUTPUT_HANDLER_HOOK_IMMUTABLE ; 
 int PHP_OUTPUT_HANDLER_START ; 
 int PHP_OUTPUT_HANDLER_STARTED ; 
#define  PHP_ZLIB_ENCODING_DEFLATE 129 
#define  PHP_ZLIB_ENCODING_GZIP 128 
 scalar_t__ SG (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZEND_STRL (char*) ; 
 int ZLIBG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compression_coding ; 
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  headers_sent ; 
 int /*<<< orphan*/  output_compression ; 
 scalar_t__ php_output_handler_hook (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  php_zlib_output_encoding () ; 
 scalar_t__ php_zlib_output_handler_ex (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sapi_add_header_ex (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int php_zlib_output_handler(void **handler_context, php_output_context *output_context)
{
	php_zlib_context *ctx = *(php_zlib_context **) handler_context;

	if (!php_zlib_output_encoding()) {
		/* "Vary: Accept-Encoding" header sent along uncompressed content breaks caching in MSIE,
			so let's just send it with successfully compressed content or unless the complete
			buffer gets discarded, see http://bugs.php.net/40325;

			Test as follows:
			+Vary: $ HTTP_ACCEPT_ENCODING=gzip ./sapi/cgi/php <<<'<?php ob_start("ob_gzhandler"); echo "foo\n";'
			+Vary: $ HTTP_ACCEPT_ENCODING= ./sapi/cgi/php <<<'<?php ob_start("ob_gzhandler"); echo "foo\n";'
			-Vary: $ HTTP_ACCEPT_ENCODING=gzip ./sapi/cgi/php <<<'<?php ob_start("ob_gzhandler"); echo "foo\n"; ob_end_clean();'
			-Vary: $ HTTP_ACCEPT_ENCODING= ./sapi/cgi/php <<<'<?php ob_start("ob_gzhandler"); echo "foo\n"; ob_end_clean();'
		*/
		if ((output_context->op & PHP_OUTPUT_HANDLER_START)
		&&	(output_context->op != (PHP_OUTPUT_HANDLER_START|PHP_OUTPUT_HANDLER_CLEAN|PHP_OUTPUT_HANDLER_FINAL))
		) {
			sapi_add_header_ex(ZEND_STRL("Vary: Accept-Encoding"), 1, 0);
		}
		return FAILURE;
	}

	if (SUCCESS != php_zlib_output_handler_ex(ctx, output_context)) {
		return FAILURE;
	}

	if (!(output_context->op & PHP_OUTPUT_HANDLER_CLEAN)) {
		int flags;

		if (SUCCESS == php_output_handler_hook(PHP_OUTPUT_HANDLER_HOOK_GET_FLAGS, &flags)) {
			/* only run this once */
			if (!(flags & PHP_OUTPUT_HANDLER_STARTED)) {
				if (SG(headers_sent) || !ZLIBG(output_compression)) {
					deflateEnd(&ctx->Z);
					return FAILURE;
				}
				switch (ZLIBG(compression_coding)) {
					case PHP_ZLIB_ENCODING_GZIP:
						sapi_add_header_ex(ZEND_STRL("Content-Encoding: gzip"), 1, 1);
						break;
					case PHP_ZLIB_ENCODING_DEFLATE:
						sapi_add_header_ex(ZEND_STRL("Content-Encoding: deflate"), 1, 1);
						break;
					default:
						deflateEnd(&ctx->Z);
						return FAILURE;
				}
				sapi_add_header_ex(ZEND_STRL("Vary: Accept-Encoding"), 1, 0);
				php_output_handler_hook(PHP_OUTPUT_HANDLER_HOOK_IMMUTABLE, NULL);
			}
		}
	}

	return SUCCESS;
}