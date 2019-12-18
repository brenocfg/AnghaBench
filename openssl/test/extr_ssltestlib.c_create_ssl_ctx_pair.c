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
typedef  int /*<<< orphan*/  SSL_METHOD ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_check_private_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_CTX_set_dh_auto (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_max_proto_version (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_min_proto_version (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

int create_ssl_ctx_pair(const SSL_METHOD *sm, const SSL_METHOD *cm,
                        int min_proto_version, int max_proto_version,
                        SSL_CTX **sctx, SSL_CTX **cctx, char *certfile,
                        char *privkeyfile)
{
    SSL_CTX *serverctx = NULL;
    SSL_CTX *clientctx = NULL;

    if (!TEST_ptr(serverctx = SSL_CTX_new(sm))
            || (cctx != NULL && !TEST_ptr(clientctx = SSL_CTX_new(cm))))
        goto err;

    if ((min_proto_version > 0
         && !TEST_true(SSL_CTX_set_min_proto_version(serverctx,
                                                     min_proto_version)))
        || (max_proto_version > 0
            && !TEST_true(SSL_CTX_set_max_proto_version(serverctx,
                                                        max_proto_version))))
        goto err;
    if (clientctx != NULL
        && ((min_proto_version > 0
             && !TEST_true(SSL_CTX_set_min_proto_version(clientctx,
                                                         min_proto_version)))
            || (max_proto_version > 0
                && !TEST_true(SSL_CTX_set_max_proto_version(clientctx,
                                                            max_proto_version)))))
        goto err;

    if (certfile != NULL && privkeyfile != NULL) {
        if (!TEST_int_eq(SSL_CTX_use_certificate_file(serverctx, certfile,
                                                      SSL_FILETYPE_PEM), 1)
                || !TEST_int_eq(SSL_CTX_use_PrivateKey_file(serverctx,
                                                            privkeyfile,
                                                            SSL_FILETYPE_PEM), 1)
                || !TEST_int_eq(SSL_CTX_check_private_key(serverctx), 1))
            goto err;
    }

#ifndef OPENSSL_NO_DH
    SSL_CTX_set_dh_auto(serverctx, 1);
#endif

    *sctx = serverctx;
    if (cctx != NULL)
        *cctx = clientctx;
    return 1;

 err:
    SSL_CTX_free(serverctx);
    SSL_CTX_free(clientctx);
    return 0;
}