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
 int /*<<< orphan*/  BIO_TYPE_WATCHCCS_FILTER ; 
 int /*<<< orphan*/ * BIO_meth_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_gets (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* method_watchccs ; 
 int /*<<< orphan*/  watchccs_ctrl ; 
 int /*<<< orphan*/  watchccs_free ; 
 int /*<<< orphan*/  watchccs_gets ; 
 int /*<<< orphan*/  watchccs_new ; 
 int /*<<< orphan*/  watchccs_puts ; 
 int /*<<< orphan*/  watchccs_read ; 
 int /*<<< orphan*/  watchccs_write ; 

__attribute__((used)) static const BIO_METHOD *bio_f_watchccs_filter(void)
{
    if (method_watchccs == NULL) {
        method_watchccs = BIO_meth_new(BIO_TYPE_WATCHCCS_FILTER,
                                       "Watch CCS filter");
        if (   method_watchccs == NULL
            || !BIO_meth_set_write(method_watchccs, watchccs_write)
            || !BIO_meth_set_read(method_watchccs, watchccs_read)
            || !BIO_meth_set_puts(method_watchccs, watchccs_puts)
            || !BIO_meth_set_gets(method_watchccs, watchccs_gets)
            || !BIO_meth_set_ctrl(method_watchccs, watchccs_ctrl)
            || !BIO_meth_set_create(method_watchccs, watchccs_new)
            || !BIO_meth_set_destroy(method_watchccs, watchccs_free))
            return NULL;
    }
    return method_watchccs;
}