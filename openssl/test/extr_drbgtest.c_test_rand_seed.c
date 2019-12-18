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
typedef  int /*<<< orphan*/  rand_buf ;
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/ * RAND_DRBG_get0_master () ; 
 int /*<<< orphan*/  RAND_DRBG_uninstantiate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_seed (unsigned char*,size_t) ; 
 int /*<<< orphan*/  RAND_status () ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_crngt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 size_t rand_drbg_seedlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_rand_seed(void)
{
    RAND_DRBG *master = NULL;
    unsigned char rand_buf[256];
    size_t rand_buflen;
    size_t required_seed_buflen = 0;

    if (!TEST_ptr(master = RAND_DRBG_get0_master())
        || !TEST_true(disable_crngt(master)))
        return 0;

#ifdef OPENSSL_RAND_SEED_NONE
    required_seed_buflen = rand_drbg_seedlen(master);
#endif

    memset(rand_buf, 0xCD, sizeof(rand_buf));

    for ( rand_buflen = 256 ; rand_buflen > 0 ; --rand_buflen ) {
        RAND_DRBG_uninstantiate(master);
        RAND_seed(rand_buf, rand_buflen);

        if (!TEST_int_eq(RAND_status(),
                         (rand_buflen >= required_seed_buflen)))
            return 0;
    }

    return 1;
}