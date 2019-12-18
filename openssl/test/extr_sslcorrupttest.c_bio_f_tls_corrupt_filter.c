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
 int /*<<< orphan*/  BIO_TYPE_CUSTOM_FILTER ; 
 int /*<<< orphan*/ * BIO_meth_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_gets (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* method_tls_corrupt ; 
 int /*<<< orphan*/  tls_corrupt_ctrl ; 
 int /*<<< orphan*/  tls_corrupt_free ; 
 int /*<<< orphan*/  tls_corrupt_gets ; 
 int /*<<< orphan*/  tls_corrupt_new ; 
 int /*<<< orphan*/  tls_corrupt_puts ; 
 int /*<<< orphan*/  tls_corrupt_read ; 
 int /*<<< orphan*/  tls_corrupt_write ; 

__attribute__((used)) static const BIO_METHOD *bio_f_tls_corrupt_filter(void)
{
    if (method_tls_corrupt == NULL) {
        method_tls_corrupt = BIO_meth_new(BIO_TYPE_CUSTOM_FILTER,
                                          "TLS corrupt filter");
        if (   method_tls_corrupt == NULL
            || !BIO_meth_set_write(method_tls_corrupt, tls_corrupt_write)
            || !BIO_meth_set_read(method_tls_corrupt, tls_corrupt_read)
            || !BIO_meth_set_puts(method_tls_corrupt, tls_corrupt_puts)
            || !BIO_meth_set_gets(method_tls_corrupt, tls_corrupt_gets)
            || !BIO_meth_set_ctrl(method_tls_corrupt, tls_corrupt_ctrl)
            || !BIO_meth_set_create(method_tls_corrupt, tls_corrupt_new)
            || !BIO_meth_set_destroy(method_tls_corrupt, tls_corrupt_free))
            return NULL;
    }
    return method_tls_corrupt;
}