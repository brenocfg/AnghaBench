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
 int /*<<< orphan*/  BIO_TYPE_TLS_DUMP_FILTER ; 
 int /*<<< orphan*/ * BIO_meth_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_gets (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* method_tls_dump ; 
 int /*<<< orphan*/  tls_dump_ctrl ; 
 int /*<<< orphan*/  tls_dump_free ; 
 int /*<<< orphan*/  tls_dump_gets ; 
 int /*<<< orphan*/  tls_dump_new ; 
 int /*<<< orphan*/  tls_dump_puts ; 
 int /*<<< orphan*/  tls_dump_read ; 
 int /*<<< orphan*/  tls_dump_write ; 

const BIO_METHOD *bio_f_tls_dump_filter(void)
{
    if (method_tls_dump == NULL) {
        method_tls_dump = BIO_meth_new(BIO_TYPE_TLS_DUMP_FILTER,
                                        "TLS dump filter");
        if (   method_tls_dump == NULL
            || !BIO_meth_set_write(method_tls_dump, tls_dump_write)
            || !BIO_meth_set_read(method_tls_dump, tls_dump_read)
            || !BIO_meth_set_puts(method_tls_dump, tls_dump_puts)
            || !BIO_meth_set_gets(method_tls_dump, tls_dump_gets)
            || !BIO_meth_set_ctrl(method_tls_dump, tls_dump_ctrl)
            || !BIO_meth_set_create(method_tls_dump, tls_dump_new)
            || !BIO_meth_set_destroy(method_tls_dump, tls_dump_free))
            return NULL;
    }
    return method_tls_dump;
}