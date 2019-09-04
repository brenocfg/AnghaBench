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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_get_data (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int BIO_write (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 

__attribute__((used)) static int md_write(BIO *b, const char *in, int inl)
{
    int ret = 0;
    EVP_MD_CTX *ctx;
    BIO *next;

    if ((in == NULL) || (inl <= 0))
        return 0;

    ctx = BIO_get_data(b);
    next = BIO_next(b);
    if ((ctx != NULL) && (next != NULL))
        ret = BIO_write(next, in, inl);

    if (BIO_get_init(b)) {
        if (ret > 0) {
            if (!EVP_DigestUpdate(ctx, (const unsigned char *)in,
                                  (unsigned int)ret)) {
                BIO_clear_retry_flags(b);
                return 0;
            }
        }
    }
    if (next != NULL) {
        BIO_clear_retry_flags(b);
        BIO_copy_next_retry(b);
    }
    return ret;
}