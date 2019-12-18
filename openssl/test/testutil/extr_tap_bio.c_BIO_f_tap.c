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
typedef  int /*<<< orphan*/  const BIO_METHOD ;

/* Variables and functions */
 int BIO_TYPE_FILTER ; 
 int BIO_TYPE_START ; 
 int /*<<< orphan*/  const* BIO_meth_new (int,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_callback_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_gets (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read_ex (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write_ex (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_callback_ctrl ; 
 int /*<<< orphan*/  tap_ctrl ; 
 int /*<<< orphan*/  tap_free ; 
 int /*<<< orphan*/  tap_gets ; 
 int /*<<< orphan*/  tap_new ; 
 int /*<<< orphan*/  tap_puts ; 
 int /*<<< orphan*/  tap_read_ex ; 
 int /*<<< orphan*/  tap_write_ex ; 

const BIO_METHOD *BIO_f_tap(void)
{
    static BIO_METHOD *tap = NULL;

    if (tap == NULL) {
        tap = BIO_meth_new(BIO_TYPE_START | BIO_TYPE_FILTER, "tap");
        if (tap != NULL) {
            BIO_meth_set_write_ex(tap, tap_write_ex);
            BIO_meth_set_read_ex(tap, tap_read_ex);
            BIO_meth_set_puts(tap, tap_puts);
            BIO_meth_set_gets(tap, tap_gets);
            BIO_meth_set_ctrl(tap, tap_ctrl);
            BIO_meth_set_create(tap, tap_new);
            BIO_meth_set_destroy(tap, tap_free);
            BIO_meth_set_callback_ctrl(tap, tap_callback_ctrl);
        }
    }
    return tap;
}