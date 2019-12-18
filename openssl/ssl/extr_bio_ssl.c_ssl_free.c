#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_1__ BIO_SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_init (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssl_free(BIO *a)
{
    BIO_SSL *bs;

    if (a == NULL)
        return 0;
    bs = BIO_get_data(a);
    if (bs->ssl != NULL)
        SSL_shutdown(bs->ssl);
    if (BIO_get_shutdown(a)) {
        if (BIO_get_init(a))
            SSL_free(bs->ssl);
        /* Clear all flags */
        BIO_clear_flags(a, ~0);
        BIO_set_init(a, 0);
    }
    OPENSSL_free(bs);
    return 1;
}