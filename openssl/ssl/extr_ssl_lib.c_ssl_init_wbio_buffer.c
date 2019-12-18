#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  wbio; int /*<<< orphan*/ * bbio; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_f_buffer () ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_read_buffer_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int /*<<< orphan*/  SSL_F_SSL_INIT_WBIO_BUFFER ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ssl_init_wbio_buffer(SSL *s)
{
    BIO *bbio;

    if (s->bbio != NULL) {
        /* Already buffered. */
        return 1;
    }

    bbio = BIO_new(BIO_f_buffer());
    if (bbio == NULL || !BIO_set_read_buffer_size(bbio, 1)) {
        BIO_free(bbio);
        SSLerr(SSL_F_SSL_INIT_WBIO_BUFFER, ERR_R_BUF_LIB);
        return 0;
    }
    s->bbio = bbio;
    s->wbio = BIO_push(bbio, s->wbio);

    return 1;
}