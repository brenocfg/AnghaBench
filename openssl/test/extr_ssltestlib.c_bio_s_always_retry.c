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
typedef  int /*<<< orphan*/  BIO_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_TYPE_ALWAYS_RETRY ; 
 int /*<<< orphan*/ * BIO_meth_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_gets (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  always_retry_ctrl ; 
 int /*<<< orphan*/  always_retry_free ; 
 int /*<<< orphan*/  always_retry_gets ; 
 int /*<<< orphan*/  always_retry_new ; 
 int /*<<< orphan*/  always_retry_puts ; 
 int /*<<< orphan*/  always_retry_read ; 
 int /*<<< orphan*/  always_retry_write ; 
 int /*<<< orphan*/  const* meth_always_retry ; 

const BIO_METHOD *bio_s_always_retry(void)
{
    if (meth_always_retry == NULL) {
        if (!TEST_ptr(meth_always_retry = BIO_meth_new(BIO_TYPE_ALWAYS_RETRY,
                                                       "Always Retry"))
            || !TEST_true(BIO_meth_set_write(meth_always_retry,
                                             always_retry_write))
            || !TEST_true(BIO_meth_set_read(meth_always_retry,
                                            always_retry_read))
            || !TEST_true(BIO_meth_set_puts(meth_always_retry,
                                            always_retry_puts))
            || !TEST_true(BIO_meth_set_gets(meth_always_retry,
                                            always_retry_gets))
            || !TEST_true(BIO_meth_set_ctrl(meth_always_retry,
                                            always_retry_ctrl))
            || !TEST_true(BIO_meth_set_create(meth_always_retry,
                                              always_retry_new))
            || !TEST_true(BIO_meth_set_destroy(meth_always_retry,
                                               always_retry_free)))
            return NULL;
    }
    return meth_always_retry;
}