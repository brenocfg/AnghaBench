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
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  SSLv23_server_method () ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static SSL_CTX *php_openssl_create_sni_server_ctx(char *cert_path, char *key_path)  /* {{{ */
{
	/* The hello method is not inherited by SSL structs when assigning a new context
	 * inside the SNI callback, so the just use SSLv23 */
	SSL_CTX *ctx = SSL_CTX_new(SSLv23_server_method());

	if (SSL_CTX_use_certificate_chain_file(ctx, cert_path) != 1) {
		php_error_docref(NULL, E_WARNING,
			"failed setting local cert chain file `%s'; " \
			"check that your cafile/capath settings include " \
			"details of your certificate and its issuer",
			cert_path
		);
		SSL_CTX_free(ctx);
		return NULL;
	} else if (SSL_CTX_use_PrivateKey_file(ctx, key_path, SSL_FILETYPE_PEM) != 1) {
		php_error_docref(NULL, E_WARNING,
			"failed setting private key from file `%s'",
			key_path
		);
		SSL_CTX_free(ctx);
		return NULL;
	}

	return ctx;
}