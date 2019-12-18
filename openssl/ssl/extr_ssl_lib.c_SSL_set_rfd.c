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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 scalar_t__ BIO_TYPE_SOCKET ; 
 scalar_t__ BIO_get_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_method_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_socket () ; 
 int /*<<< orphan*/  BIO_set_fd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int /*<<< orphan*/  SSL_F_SSL_SET_RFD ; 
 int /*<<< orphan*/ * SSL_get_wbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set0_rbio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int SSL_set_rfd(SSL *s, int fd)
{
    BIO *wbio = SSL_get_wbio(s);

    if (wbio == NULL || BIO_method_type(wbio) != BIO_TYPE_SOCKET
        || ((int)BIO_get_fd(wbio, NULL) != fd)) {
        BIO *bio = BIO_new(BIO_s_socket());

        if (bio == NULL) {
            SSLerr(SSL_F_SSL_SET_RFD, ERR_R_BUF_LIB);
            return 0;
        }
        BIO_set_fd(bio, fd, BIO_NOCLOSE);
        SSL_set0_rbio(s, bio);
    } else {
        BIO_up_ref(wbio);
        SSL_set0_rbio(s, wbio);
    }

    return 1;
}