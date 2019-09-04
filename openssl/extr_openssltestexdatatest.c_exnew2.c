#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int new; } ;
typedef  TYPE_1__ MYOBJ_EX_DATA ;
typedef  int /*<<< orphan*/  CRYPTO_EX_DATA ;

/* Variables and functions */
 int CRYPTO_set_ex_data (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_long_eq (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_ptr_eq (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr_null (void*) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 scalar_t__ gbl_result ; 
 int /*<<< orphan*/  saved_argl ; 
 int /*<<< orphan*/  saved_argp ; 
 int saved_idx2 ; 
 int saved_idx3 ; 

__attribute__((used)) static void exnew2(void *parent, void *ptr, CRYPTO_EX_DATA *ad,
          int idx, long argl, void *argp)
{
    MYOBJ_EX_DATA *ex_data = OPENSSL_zalloc(sizeof(*ex_data));

    if (!TEST_true(idx == saved_idx2 || idx == saved_idx3)
        || !TEST_long_eq(argl, saved_argl)
        || !TEST_ptr_eq(argp, saved_argp)
        || !TEST_ptr_null(ptr)
        || !TEST_ptr(ex_data)
        || !TEST_true(CRYPTO_set_ex_data(ad, idx, ex_data))) {
        gbl_result = 0;
        OPENSSL_free(ex_data);
    } else {
        ex_data->new = 1;
    }
}