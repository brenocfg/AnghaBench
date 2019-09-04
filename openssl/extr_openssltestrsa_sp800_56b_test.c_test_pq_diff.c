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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 scalar_t__ TEST_false (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsa_check_pminusq_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int test_pq_diff(void)
{
    int ret = 0;
    BIGNUM *tmp = NULL, *p = NULL, *q = NULL;

    ret = TEST_ptr(tmp = BN_new())
          && TEST_ptr(p = BN_new())
          && TEST_ptr(q = BN_new())
          /* |1-(2+1)| > 2^1 */
          && TEST_true(BN_set_word(p, 1))
          && TEST_true(BN_set_word(q, 1+2))
          && TEST_false(rsa_check_pminusq_diff(tmp, p, q, 202))
          /* Check |p - q| > 2^(nbits/2 - 100) */
          && TEST_true(BN_set_word(q, 1+3))
          && TEST_true(rsa_check_pminusq_diff(tmp, p, q, 202))
          && TEST_true(BN_set_word(p, 1+3))
          && TEST_true(BN_set_word(q, 1))
          && TEST_true(rsa_check_pminusq_diff(tmp, p, q, 202));
    BN_free(p);
    BN_free(q);
    BN_free(tmp);
    return ret;
}