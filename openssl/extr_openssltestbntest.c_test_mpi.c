#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  scratch ;
struct TYPE_3__ {int /*<<< orphan*/  mpi_len; int /*<<< orphan*/  mpi; int /*<<< orphan*/  base10; } ;
typedef  TYPE_1__ MPITEST ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_asc2bn (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 size_t BN_bn2mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_mpi2bn (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  TEST_BN_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,size_t) ; 
 int /*<<< orphan*/  TEST_size_t_le (size_t,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* kMPITests ; 

__attribute__((used)) static int test_mpi(int i)
{
    uint8_t scratch[8];
    const MPITEST *test = &kMPITests[i];
    size_t mpi_len, mpi_len2;
    BIGNUM *bn = NULL;
    BIGNUM *bn2 = NULL;
    int st = 0;

    if (!TEST_ptr(bn = BN_new())
            || !TEST_true(BN_asc2bn(&bn, test->base10)))
        goto err;
    mpi_len = BN_bn2mpi(bn, NULL);
    if (!TEST_size_t_le(mpi_len, sizeof(scratch)))
        goto err;

    if (!TEST_size_t_eq(mpi_len2 = BN_bn2mpi(bn, scratch), mpi_len)
            || !TEST_mem_eq(test->mpi, test->mpi_len, scratch, mpi_len))
        goto err;

    if (!TEST_ptr(bn2 = BN_mpi2bn(scratch, mpi_len, NULL)))
        goto err;

    if (!TEST_BN_eq(bn, bn2)) {
        BN_free(bn2);
        goto err;
    }
    BN_free(bn2);

    st = 1;
 err:
    BN_free(bn);
    return st;
}