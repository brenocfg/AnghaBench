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
typedef  int /*<<< orphan*/  BIO_SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_F_SSL_NEW ; 
 int /*<<< orphan*/  BIO_clear_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

__attribute__((used)) static int ssl_new(BIO *bi)
{
    BIO_SSL *bs = OPENSSL_zalloc(sizeof(*bs));

    if (bs == NULL) {
        BIOerr(BIO_F_SSL_NEW, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    BIO_set_init(bi, 0);
    BIO_set_data(bi, bs);
    /* Clear all flags */
    BIO_clear_flags(bi, ~0);

    return 1;
}