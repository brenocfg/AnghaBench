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
typedef  int /*<<< orphan*/  CRYPTO_EX_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_long_eq (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr_eq (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr_null (void*) ; 
 scalar_t__ gbl_result ; 
 int /*<<< orphan*/  saved_argl ; 
 int /*<<< orphan*/  saved_argp ; 
 int /*<<< orphan*/  saved_idx ; 

__attribute__((used)) static void exnew(void *parent, void *ptr, CRYPTO_EX_DATA *ad,
          int idx, long argl, void *argp)
{
    if (!TEST_int_eq(idx, saved_idx)
        || !TEST_long_eq(argl, saved_argl)
        || !TEST_ptr_eq(argp, saved_argp)
        || !TEST_ptr_null(ptr))
        gbl_result = 0;
}