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
 int /*<<< orphan*/  BIO_TYPE_FILTER ; 
 int /*<<< orphan*/  BIO_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_meth_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_callback_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefix_callback_ctrl ; 
 int /*<<< orphan*/  prefix_create ; 
 int /*<<< orphan*/  prefix_ctrl ; 
 int /*<<< orphan*/  prefix_destroy ; 
 int /*<<< orphan*/  prefix_gets ; 
 int /*<<< orphan*/ * prefix_meth ; 
 int /*<<< orphan*/  prefix_puts ; 
 int /*<<< orphan*/  prefix_read ; 
 int /*<<< orphan*/  prefix_write ; 

BIO_METHOD *apps_bf_prefix(void)
{
    if (prefix_meth == NULL) {
        if ((prefix_meth =
             BIO_meth_new(BIO_TYPE_FILTER, "Prefix filter")) == NULL
            || !BIO_meth_set_create(prefix_meth, prefix_create)
            || !BIO_meth_set_destroy(prefix_meth, prefix_destroy)
            || !BIO_meth_set_write_ex(prefix_meth, prefix_write)
            || !BIO_meth_set_read_ex(prefix_meth, prefix_read)
            || !BIO_meth_set_puts(prefix_meth, prefix_puts)
            || !BIO_meth_set_gets(prefix_meth, prefix_gets)
            || !BIO_meth_set_ctrl(prefix_meth, prefix_ctrl)
            || !BIO_meth_set_callback_ctrl(prefix_meth, prefix_callback_ctrl)) {
            BIO_meth_free(prefix_meth);
            prefix_meth = NULL;
        }
    }
    return prefix_meth;
}