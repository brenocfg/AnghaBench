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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  php_stream ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int /*<<< orphan*/  GET_VER_OPT_STRING (char*,char const*) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SSL_CTX_check_private_key (int /*<<< orphan*/ *) ; 
 int SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int SUCCESS ; 
 scalar_t__ VCWD_REALPATH (char const*,char*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int php_openssl_set_local_cert(SSL_CTX *ctx, php_stream *stream) /* {{{ */
{
	zval *val = NULL;
	char *certfile = NULL;

	GET_VER_OPT_STRING("local_cert", certfile);

	if (certfile) {
		char resolved_path_buff[MAXPATHLEN];
		const char *private_key = NULL;

		if (VCWD_REALPATH(certfile, resolved_path_buff)) {
			/* a certificate to use for authentication */
			if (SSL_CTX_use_certificate_chain_file(ctx, resolved_path_buff) != 1) {
				php_error_docref(NULL, E_WARNING,
					"Unable to set local cert chain file `%s'; Check that your cafile/capath "
					"settings include details of your certificate and its issuer",
					certfile);
				return FAILURE;
			}
			GET_VER_OPT_STRING("local_pk", private_key);

			if (private_key) {
				char resolved_path_buff_pk[MAXPATHLEN];
				if (VCWD_REALPATH(private_key, resolved_path_buff_pk)) {
					if (SSL_CTX_use_PrivateKey_file(ctx, resolved_path_buff_pk, SSL_FILETYPE_PEM) != 1) {
						php_error_docref(NULL, E_WARNING, "Unable to set private key file `%s'", resolved_path_buff_pk);
						return FAILURE;
					}
				}
			} else {
				if (SSL_CTX_use_PrivateKey_file(ctx, resolved_path_buff, SSL_FILETYPE_PEM) != 1) {
					php_error_docref(NULL, E_WARNING, "Unable to set private key file `%s'", resolved_path_buff);
					return FAILURE;
				}
			}

			if (!SSL_CTX_check_private_key(ctx)) {
				php_error_docref(NULL, E_WARNING, "Private key does not match certificate!");
			}
		}
	}

	return SUCCESS;
}