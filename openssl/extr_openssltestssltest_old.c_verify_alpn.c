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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get0_alpn_selected (int /*<<< orphan*/ *,unsigned char const**,unsigned int*) ; 
 scalar_t__ SSL_get_SSL_CTX (int /*<<< orphan*/ *) ; 
 unsigned char const* alpn_client ; 
 unsigned char const* alpn_expected ; 
 int /*<<< orphan*/ * alpn_selected ; 
 unsigned char const* alpn_server ; 
 unsigned char const* alpn_server2 ; 
 int /*<<< orphan*/  bio_stdout ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char const*,unsigned int) ; 
 scalar_t__ s_ctx2 ; 
 unsigned int strlen (unsigned char const*) ; 

__attribute__((used)) static int verify_alpn(SSL *client, SSL *server)
{
    const unsigned char *client_proto, *server_proto;
    unsigned int client_proto_len = 0, server_proto_len = 0;
    SSL_get0_alpn_selected(client, &client_proto, &client_proto_len);
    SSL_get0_alpn_selected(server, &server_proto, &server_proto_len);

    OPENSSL_free(alpn_selected);
    alpn_selected = NULL;

    if (client_proto_len != server_proto_len) {
        BIO_printf(bio_stdout, "ALPN selected protocols differ!\n");
        goto err;
    }

    if (client_proto != NULL &&
        memcmp(client_proto, server_proto, client_proto_len) != 0) {
        BIO_printf(bio_stdout, "ALPN selected protocols differ!\n");
        goto err;
    }

    if (client_proto_len > 0 && alpn_expected == NULL) {
        BIO_printf(bio_stdout, "ALPN unexpectedly negotiated\n");
        goto err;
    }

    if (alpn_expected != NULL &&
        (client_proto_len != strlen(alpn_expected) ||
         memcmp(client_proto, alpn_expected, client_proto_len) != 0)) {
        BIO_printf(bio_stdout,
                   "ALPN selected protocols not equal to expected protocol: %s\n",
                   alpn_expected);
        goto err;
    }

    return 0;

 err:
    BIO_printf(bio_stdout, "ALPN results: client: '");
    BIO_write(bio_stdout, client_proto, client_proto_len);
    BIO_printf(bio_stdout, "', server: '");
    BIO_write(bio_stdout, server_proto, server_proto_len);
    BIO_printf(bio_stdout, "'\n");
    BIO_printf(bio_stdout, "ALPN configured: client: '%s', server: '",
                   alpn_client);
    if (SSL_get_SSL_CTX(server) == s_ctx2) {
        BIO_printf(bio_stdout, "%s'\n",
                   alpn_server2);
    } else {
        BIO_printf(bio_stdout, "%s'\n",
                   alpn_server);
    }
    return -1;
}