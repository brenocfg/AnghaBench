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
typedef  unsigned char DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int DH_CHECK_P_NOT_PRIME ; 
 int DH_CHECK_P_NOT_SAFE_PRIME ; 
 int DH_NOT_SUITABLE_GENERATOR ; 
 int DH_UNABLE_TO_CHECK_GENERATOR ; 
 int /*<<< orphan*/  DH_check (unsigned char*,int*) ; 
 int DH_compute_key (unsigned char*,int /*<<< orphan*/  const*,unsigned char*) ; 
 int /*<<< orphan*/  DH_free (unsigned char*) ; 
 int /*<<< orphan*/  DH_generate_key (unsigned char*) ; 
 int /*<<< orphan*/  DH_get0_key (unsigned char*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 unsigned char* DH_new_by_nid (int /*<<< orphan*/ ) ; 
 int DH_size (unsigned char*) ; 
 int /*<<< orphan*/  NID_ffdhe2048 ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  TEST_false (int) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  TEST_true (int) ; 

__attribute__((used)) static int rfc7919_test(void)
{
    DH *a = NULL, *b = NULL;
    const BIGNUM *apub_key = NULL, *bpub_key = NULL;
    unsigned char *abuf = NULL;
    unsigned char *bbuf = NULL;
    int i, alen, blen, aout, bout;
    int ret = 0;

    if (!TEST_ptr(a = DH_new_by_nid(NID_ffdhe2048)))
         goto err;

    if (!DH_check(a, &i))
        goto err;
    if (!TEST_false(i & DH_CHECK_P_NOT_PRIME)
            || !TEST_false(i & DH_CHECK_P_NOT_SAFE_PRIME)
            || !TEST_false(i & DH_UNABLE_TO_CHECK_GENERATOR)
            || !TEST_false(i & DH_NOT_SUITABLE_GENERATOR)
            || !TEST_false(i))
        goto err;

    if (!DH_generate_key(a))
        goto err;
    DH_get0_key(a, &apub_key, NULL);

    /* now create another copy of the DH group for the peer */
    if (!TEST_ptr(b = DH_new_by_nid(NID_ffdhe2048)))
        goto err;

    if (!DH_generate_key(b))
        goto err;
    DH_get0_key(b, &bpub_key, NULL);

    alen = DH_size(a);
    if (!TEST_ptr(abuf = OPENSSL_malloc(alen))
            || !TEST_true((aout = DH_compute_key(abuf, bpub_key, a)) != -1))
        goto err;

    blen = DH_size(b);
    if (!TEST_ptr(bbuf = OPENSSL_malloc(blen))
            || !TEST_true((bout = DH_compute_key(bbuf, apub_key, b)) != -1))
        goto err;

    if (!TEST_true(aout >= 20)
            || !TEST_mem_eq(abuf, aout, bbuf, bout))
        goto err;

    ret = 1;

 err:
    OPENSSL_free(abuf);
    OPENSSL_free(bbuf);
    DH_free(a);
    DH_free(b);
    return ret;
}