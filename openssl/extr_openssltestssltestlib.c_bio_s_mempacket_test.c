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
 int /*<<< orphan*/  BIO_TYPE_MEMPACKET_TEST ; 
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
 int /*<<< orphan*/  mempacket_test_ctrl ; 
 int /*<<< orphan*/  mempacket_test_free ; 
 int /*<<< orphan*/  mempacket_test_gets ; 
 int /*<<< orphan*/  mempacket_test_new ; 
 int /*<<< orphan*/  mempacket_test_puts ; 
 int /*<<< orphan*/  mempacket_test_read ; 
 int /*<<< orphan*/  mempacket_test_write ; 
 int /*<<< orphan*/  const* meth_mem ; 

const BIO_METHOD *bio_s_mempacket_test(void)
{
    if (meth_mem == NULL) {
        if (!TEST_ptr(meth_mem = BIO_meth_new(BIO_TYPE_MEMPACKET_TEST,
                                              "Mem Packet Test"))
            || !TEST_true(BIO_meth_set_write(meth_mem, mempacket_test_write))
            || !TEST_true(BIO_meth_set_read(meth_mem, mempacket_test_read))
            || !TEST_true(BIO_meth_set_puts(meth_mem, mempacket_test_puts))
            || !TEST_true(BIO_meth_set_gets(meth_mem, mempacket_test_gets))
            || !TEST_true(BIO_meth_set_ctrl(meth_mem, mempacket_test_ctrl))
            || !TEST_true(BIO_meth_set_create(meth_mem, mempacket_test_new))
            || !TEST_true(BIO_meth_set_destroy(meth_mem, mempacket_test_free)))
            return NULL;
    }
    return meth_mem;
}