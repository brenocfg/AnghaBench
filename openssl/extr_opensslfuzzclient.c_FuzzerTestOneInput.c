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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int SSL_do_handshake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSL_set_cipher_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 int SSL_set_min_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_tlsext_host_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSLv23_method () ; 

int FuzzerTestOneInput(const uint8_t *buf, size_t len)
{
    SSL *client;
    BIO *in;
    BIO *out;
    SSL_CTX *ctx;

    if (len == 0)
        return 0;

    /*
     * TODO: use the ossltest engine (optionally?) to disable crypto checks.
     */

    /* This only fuzzes the initial flow from the client so far. */
    ctx = SSL_CTX_new(SSLv23_method());

    client = SSL_new(ctx);
    OPENSSL_assert(SSL_set_min_proto_version(client, 0) == 1);
    OPENSSL_assert(SSL_set_cipher_list(client, "ALL:eNULL:@SECLEVEL=0") == 1);
    SSL_set_tlsext_host_name(client, "localhost");
    in = BIO_new(BIO_s_mem());
    out = BIO_new(BIO_s_mem());
    SSL_set_bio(client, in, out);
    SSL_set_connect_state(client);
    OPENSSL_assert((size_t)BIO_write(in, buf, len) == len);
    if (SSL_do_handshake(client) == 1) {
        /* Keep reading application data until error or EOF. */
        uint8_t tmp[1024];
        for (;;) {
            if (SSL_read(client, tmp, sizeof(tmp)) <= 0) {
                break;
            }
        }
    }
    SSL_free(client);
    ERR_clear_error();
    SSL_CTX_free(ctx);

    return 0;
}