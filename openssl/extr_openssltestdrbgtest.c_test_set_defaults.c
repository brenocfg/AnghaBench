#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 int NID_aes_256_ctr ; 
 int NID_sha1 ; 
 int NID_sha256 ; 
 int RAND_DRBG_FLAGS ; 
 int RAND_DRBG_FLAG_CTR_NO_DF ; 
 int RAND_DRBG_FLAG_HMAC ; 
 int RAND_DRBG_FLAG_MASTER ; 
 int RAND_DRBG_FLAG_PRIVATE ; 
 int RAND_DRBG_FLAG_PUBLIC ; 
 int RAND_DRBG_TYPE ; 
 TYPE_1__* RAND_DRBG_get0_master () ; 
 TYPE_1__* RAND_DRBG_get0_private () ; 
 TYPE_1__* RAND_DRBG_get0_public () ; 
 int /*<<< orphan*/  RAND_DRBG_set_defaults (int,int) ; 
 int /*<<< orphan*/  RAND_DRBG_uninstantiate (TYPE_1__*) ; 
 scalar_t__ TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TEST_ptr (TYPE_1__*) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_set_defaults(void)
{
    RAND_DRBG *master = NULL, *public = NULL, *private = NULL;

           /* Check the default type and flags for master, public and private */
    return TEST_ptr(master = RAND_DRBG_get0_master())
           && TEST_ptr(public = RAND_DRBG_get0_public())
           && TEST_ptr(private = RAND_DRBG_get0_private())
           && TEST_int_eq(master->type, RAND_DRBG_TYPE)
           && TEST_int_eq(master->flags,
                          RAND_DRBG_FLAGS | RAND_DRBG_FLAG_MASTER)
           && TEST_int_eq(public->type, RAND_DRBG_TYPE)
           && TEST_int_eq(public->flags,
                          RAND_DRBG_FLAGS | RAND_DRBG_FLAG_PUBLIC)
           && TEST_int_eq(private->type, RAND_DRBG_TYPE)
           && TEST_int_eq(private->flags,
                          RAND_DRBG_FLAGS | RAND_DRBG_FLAG_PRIVATE)

           /* change master DRBG and check again */
           && TEST_true(RAND_DRBG_set_defaults(NID_sha256,
                                               RAND_DRBG_FLAG_MASTER))
           && TEST_true(RAND_DRBG_uninstantiate(master))
           && TEST_int_eq(master->type, NID_sha256)
           && TEST_int_eq(master->flags, RAND_DRBG_FLAG_MASTER)
           && TEST_int_eq(public->type, RAND_DRBG_TYPE)
           && TEST_int_eq(public->flags,
                          RAND_DRBG_FLAGS | RAND_DRBG_FLAG_PUBLIC)
           && TEST_int_eq(private->type, RAND_DRBG_TYPE)
           && TEST_int_eq(private->flags,
                          RAND_DRBG_FLAGS | RAND_DRBG_FLAG_PRIVATE)
           /* change private DRBG and check again */
           && TEST_true(RAND_DRBG_set_defaults(NID_sha256,
                        RAND_DRBG_FLAG_PRIVATE|RAND_DRBG_FLAG_HMAC))
           && TEST_true(RAND_DRBG_uninstantiate(private))
           && TEST_int_eq(master->type, NID_sha256)
           && TEST_int_eq(master->flags, RAND_DRBG_FLAG_MASTER)
           && TEST_int_eq(public->type, RAND_DRBG_TYPE)
           && TEST_int_eq(public->flags,
                          RAND_DRBG_FLAGS | RAND_DRBG_FLAG_PUBLIC)
           && TEST_int_eq(private->type, NID_sha256)
           && TEST_int_eq(private->flags,
                          RAND_DRBG_FLAG_PRIVATE | RAND_DRBG_FLAG_HMAC)
           /* change public DRBG and check again */
           && TEST_true(RAND_DRBG_set_defaults(NID_sha1,
                                               RAND_DRBG_FLAG_PUBLIC
                                               | RAND_DRBG_FLAG_HMAC))
           && TEST_true(RAND_DRBG_uninstantiate(public))
           && TEST_int_eq(master->type, NID_sha256)
           && TEST_int_eq(master->flags, RAND_DRBG_FLAG_MASTER)
           && TEST_int_eq(public->type, NID_sha1)
           && TEST_int_eq(public->flags,
                          RAND_DRBG_FLAG_PUBLIC | RAND_DRBG_FLAG_HMAC)
           && TEST_int_eq(private->type, NID_sha256)
           && TEST_int_eq(private->flags,
                          RAND_DRBG_FLAG_PRIVATE | RAND_DRBG_FLAG_HMAC)
           /* Change DRBG defaults and change public and check again */
           && TEST_true(RAND_DRBG_set_defaults(NID_sha256, 0))
           && TEST_true(RAND_DRBG_uninstantiate(public))
           && TEST_int_eq(public->type, NID_sha256)
           && TEST_int_eq(public->flags, RAND_DRBG_FLAG_PUBLIC)

          /* FIPS mode doesn't support CTR DRBG without a derivation function */
#ifndef FIPS_MODE
          /* Change DRBG defaults and change master and check again */
           && TEST_true(RAND_DRBG_set_defaults(NID_aes_256_ctr,
                                               RAND_DRBG_FLAG_CTR_NO_DF))
           && TEST_true(RAND_DRBG_uninstantiate(master))
           && TEST_int_eq(master->type, NID_aes_256_ctr)
           && TEST_int_eq(master->flags,
                          RAND_DRBG_FLAG_MASTER|RAND_DRBG_FLAG_CTR_NO_DF)
#endif
           /* Reset back to the standard defaults */
           && TEST_true(RAND_DRBG_set_defaults(RAND_DRBG_TYPE,
                                               RAND_DRBG_FLAGS
                                               | RAND_DRBG_FLAG_MASTER
                                               | RAND_DRBG_FLAG_PUBLIC
                                               | RAND_DRBG_FLAG_PRIVATE))
           && TEST_true(RAND_DRBG_uninstantiate(master))
           && TEST_true(RAND_DRBG_uninstantiate(public))
           && TEST_true(RAND_DRBG_uninstantiate(private));
}