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
 int /*<<< orphan*/  SSL_ERROR_WANT_READ ; 
 int /*<<< orphan*/  SSL_get_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SSL_read_ex (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ulong_eq (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_bare_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

int create_ssl_connection(SSL *serverssl, SSL *clientssl, int want)
{
    int i;
    unsigned char buf;
    size_t readbytes;

    if (!create_bare_ssl_connection(serverssl, clientssl, want, 1))
        return 0;

    /*
     * We attempt to read some data on the client side which we expect to fail.
     * This will ensure we have received the NewSessionTicket in TLSv1.3 where
     * appropriate. We do this twice because there are 2 NewSessionTickets.
     */
    for (i = 0; i < 2; i++) {
        if (SSL_read_ex(clientssl, &buf, sizeof(buf), &readbytes) > 0) {
            if (!TEST_ulong_eq(readbytes, 0))
                return 0;
        } else if (!TEST_int_eq(SSL_get_error(clientssl, 0),
                                SSL_ERROR_WANT_READ)) {
            return 0;
        }
    }

    return 1;
}