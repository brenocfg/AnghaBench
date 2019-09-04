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
 int /*<<< orphan*/  BIO_TYPE_ASYNC_FILTER ; 
 int /*<<< orphan*/ * BIO_meth_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_gets (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_ctrl ; 
 int /*<<< orphan*/  async_free ; 
 int /*<<< orphan*/  async_gets ; 
 int /*<<< orphan*/  async_new ; 
 int /*<<< orphan*/  async_puts ; 
 int /*<<< orphan*/  async_read ; 
 int /*<<< orphan*/  async_write ; 
 int /*<<< orphan*/  const* methods_async ; 

__attribute__((used)) static const BIO_METHOD *bio_f_async_filter(void)
{
    if (methods_async == NULL) {
        methods_async = BIO_meth_new(BIO_TYPE_ASYNC_FILTER, "Async filter");
        if (   methods_async == NULL
            || !BIO_meth_set_write(methods_async, async_write)
            || !BIO_meth_set_read(methods_async, async_read)
            || !BIO_meth_set_puts(methods_async, async_puts)
            || !BIO_meth_set_gets(methods_async, async_gets)
            || !BIO_meth_set_ctrl(methods_async, async_ctrl)
            || !BIO_meth_set_create(methods_async, async_new)
            || !BIO_meth_set_destroy(methods_async, async_free))
            return NULL;
    }
    return methods_async;
}