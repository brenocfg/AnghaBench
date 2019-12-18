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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int MAXLOOPS ; 
 int SSL_ERROR_NONE ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int SSL_ERROR_WANT_X509_LOOKUP ; 
 int SSL_accept (int /*<<< orphan*/ *) ; 
 int SSL_connect (int /*<<< orphan*/ *) ; 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int SSL_is_dtls (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_info (char*,...) ; 
 int /*<<< orphan*/  ossl_sleep (int) ; 

int create_bare_ssl_connection(SSL *serverssl, SSL *clientssl, int want,
                               int read)
{
    int retc = -1, rets = -1, err, abortctr = 0;
    int clienterr = 0, servererr = 0;
    int isdtls = SSL_is_dtls(serverssl);

    do {
        err = SSL_ERROR_WANT_WRITE;
        while (!clienterr && retc <= 0 && err == SSL_ERROR_WANT_WRITE) {
            retc = SSL_connect(clientssl);
            if (retc <= 0)
                err = SSL_get_error(clientssl, retc);
        }

        if (!clienterr && retc <= 0 && err != SSL_ERROR_WANT_READ) {
            TEST_info("SSL_connect() failed %d, %d", retc, err);
            clienterr = 1;
        }
        if (want != SSL_ERROR_NONE && err == want)
            return 0;

        err = SSL_ERROR_WANT_WRITE;
        while (!servererr && rets <= 0 && err == SSL_ERROR_WANT_WRITE) {
            rets = SSL_accept(serverssl);
            if (rets <= 0)
                err = SSL_get_error(serverssl, rets);
        }

        if (!servererr && rets <= 0
                && err != SSL_ERROR_WANT_READ
                && err != SSL_ERROR_WANT_X509_LOOKUP) {
            TEST_info("SSL_accept() failed %d, %d", rets, err);
            servererr = 1;
        }
        if (want != SSL_ERROR_NONE && err == want)
            return 0;
        if (clienterr && servererr)
            return 0;
        if (isdtls && read) {
            unsigned char buf[20];

            /* Trigger any retransmits that may be appropriate */
            if (rets > 0 && retc <= 0) {
                if (SSL_read(serverssl, buf, sizeof(buf)) > 0) {
                    /* We don't expect this to succeed! */
                    TEST_info("Unexpected SSL_read() success!");
                    return 0;
                }
            }
            if (retc > 0 && rets <= 0) {
                if (SSL_read(clientssl, buf, sizeof(buf)) > 0) {
                    /* We don't expect this to succeed! */
                    TEST_info("Unexpected SSL_read() success!");
                    return 0;
                }
            }
        }
        if (++abortctr == MAXLOOPS) {
            TEST_info("No progress made");
            return 0;
        }
        if (isdtls && abortctr <= 50 && (abortctr % 10) == 0) {
            /*
             * It looks like we're just spinning. Pause for a short period to
             * give the DTLS timer a chance to do something. We only do this for
             * the first few times to prevent hangs.
             */
            ossl_sleep(50);
        }
    } while (retc <=0 || rets <= 0);

    return 1;
}