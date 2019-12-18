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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int /*<<< orphan*/  BIO_set_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_DISABLE ; 
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_ENABLE ; 
 int /*<<< orphan*/  CRYPTO_mem_ctrl (int /*<<< orphan*/ ) ; 
 int CRYPTO_mem_leaks_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_bio ; 

int CRYPTO_mem_leaks_fp(FILE *fp)
{
    BIO *b;
    int ret;

    /*
     * Need to turn off memory checking when allocated BIOs ... especially as
     * we're creating them at a time when we're trying to check we've not
     * left anything un-free()'d!!
     */
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_DISABLE);
    b = BIO_new(BIO_s_file());
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ENABLE);
    if (b == NULL)
        return -1;
    BIO_set_fp(b, fp, BIO_NOCLOSE);
    ret = CRYPTO_mem_leaks_cb(print_bio, b);
    BIO_free(b);
    return ret;
}