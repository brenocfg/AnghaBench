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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 size_t BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 size_t DTLS_get_data_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_OP_NO_ENCRYPT_THEN_MAC ; 
 scalar_t__ SSL_READ_ETM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_rbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_cipher_list (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  SSL_set_mtu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_write (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  TEST_error (char*,char const*,unsigned long,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  TEST_false (int) ; 
 int /*<<< orphan*/  TEST_info (char*,...) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_size_t_ne (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 

__attribute__((used)) static int mtu_test(SSL_CTX *ctx, const char *cs, int no_etm)
{
    SSL *srvr_ssl = NULL, *clnt_ssl = NULL;
    BIO *sc_bio = NULL;
    int i;
    size_t s;
    size_t mtus[30];
    unsigned char buf[600];
    int rv = 0;

    memset(buf, 0x5a, sizeof(buf));

    if (!TEST_true(create_ssl_objects(ctx, ctx, &srvr_ssl, &clnt_ssl,
                                      NULL, NULL)))
        goto end;

    if (no_etm)
        SSL_set_options(srvr_ssl, SSL_OP_NO_ENCRYPT_THEN_MAC);

    if (!TEST_true(SSL_set_cipher_list(srvr_ssl, cs))
            || !TEST_true(SSL_set_cipher_list(clnt_ssl, cs))
            || !TEST_ptr(sc_bio = SSL_get_rbio(srvr_ssl))
            || !TEST_true(create_ssl_connection(clnt_ssl, srvr_ssl,
                                                SSL_ERROR_NONE)))
        goto end;

    if (debug)
        TEST_info("Channel established");

    /* For record MTU values between 500 and 539, call DTLS_get_data_mtu()
     * to query the payload MTU which will fit. */
    for (i = 0; i < 30; i++) {
        SSL_set_mtu(clnt_ssl, 500 + i);
        mtus[i] = DTLS_get_data_mtu(clnt_ssl);
        if (debug)
            TEST_info("%s%s MTU for record mtu %d = %lu",
                      cs, no_etm ? "-noEtM" : "",
                      500 + i, (unsigned long)mtus[i]);
        if (!TEST_size_t_ne(mtus[i], 0)) {
            TEST_info("Cipher %s MTU %d", cs, 500 + i);
            goto end;
        }
    }

    /* Now get out of the way */
    SSL_set_mtu(clnt_ssl, 1000);

    /*
     * Now for all values in the range of payload MTUs, send a payload of
     * that size and see what actual record size we end up with.
     */
    for (s = mtus[0]; s <= mtus[29]; s++) {
        size_t reclen;

        if (!TEST_int_eq(SSL_write(clnt_ssl, buf, s), (int)s))
            goto end;
        reclen = BIO_read(sc_bio, buf, sizeof(buf));
        if (debug)
            TEST_info("record %zu for payload %zu", reclen, s);

        for (i = 0; i < 30; i++) {
            /* DTLS_get_data_mtu() with record MTU 500+i returned mtus[i] ... */

            if (!TEST_false(s <= mtus[i] && reclen > (size_t)(500 + i))) {
                /*
                 * We sent a packet smaller than or equal to mtus[j] and
                 * that made a record *larger* than the record MTU 500+j!
                 */
                TEST_error("%s: s=%lu, mtus[i]=%lu, reclen=%lu, i=%d",
                           cs, (unsigned long)s, (unsigned long)mtus[i],
                           (unsigned long)reclen, 500 + i);
                goto end;
            }
            if (!TEST_false(s > mtus[i] && reclen <= (size_t)(500 + i))) {
                /*
                 * We sent a *larger* packet than mtus[i] and that *still*
                 * fits within the record MTU 500+i, so DTLS_get_data_mtu()
                 * was overly pessimistic.
                 */
                TEST_error("%s: s=%lu, mtus[i]=%lu, reclen=%lu, i=%d",
                           cs, (unsigned long)s, (unsigned long)mtus[i],
                           (unsigned long)reclen, 500 + i);
                goto end;
            }
        }
    }
    rv = 1;
    if (SSL_READ_ETM(clnt_ssl))
        rv = 2;
 end:
    SSL_free(clnt_ssl);
    SSL_free(srvr_ssl);
    return rv;
}