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

/* Variables and functions */
 int CRYPTO_secure_allocated (char*) ; 
 int CRYPTO_secure_malloc_done () ; 
 int CRYPTO_secure_malloc_init (int,int) ; 
 int CRYPTO_secure_malloc_initialized () ; 
 int /*<<< orphan*/  CRYPTO_secure_used () ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  OPENSSL_secure_clear_free (char*,int) ; 
 int /*<<< orphan*/  OPENSSL_secure_free (char*) ; 
 char* OPENSSL_secure_malloc (size_t) ; 
 int TEST_false (int) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 int /*<<< orphan*/  TEST_ptr_null (char*) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TEST_true (int) ; 

__attribute__((used)) static int test_sec_mem(void)
{
#ifdef OPENSSL_SECURE_MEMORY
    int testresult = 0;
    char *p = NULL, *q = NULL, *r = NULL, *s = NULL;

    TEST_info("Secure memory is implemented.");

    s = OPENSSL_secure_malloc(20);
    /* s = non-secure 20 */
    if (!TEST_ptr(s)
        || !TEST_false(CRYPTO_secure_allocated(s)))
        goto end;
    r = OPENSSL_secure_malloc(20);
    /* r = non-secure 20, s = non-secure 20 */
    if (!TEST_ptr(r)
        || !TEST_true(CRYPTO_secure_malloc_init(4096, 32))
        || !TEST_false(CRYPTO_secure_allocated(r)))
        goto end;
    p = OPENSSL_secure_malloc(20);
    if (!TEST_ptr(p)
        /* r = non-secure 20, p = secure 20, s = non-secure 20 */
        || !TEST_true(CRYPTO_secure_allocated(p))
        /* 20 secure -> 32-byte minimum allocation unit */
        || !TEST_size_t_eq(CRYPTO_secure_used(), 32))
        goto end;
    q = OPENSSL_malloc(20);
    if (!TEST_ptr(q))
        goto end;
    /* r = non-secure 20, p = secure 20, q = non-secure 20, s = non-secure 20 */
    if (!TEST_false(CRYPTO_secure_allocated(q)))
        goto end;
    OPENSSL_secure_clear_free(s, 20);
    s = OPENSSL_secure_malloc(20);
    if (!TEST_ptr(s)
        /* r = non-secure 20, p = secure 20, q = non-secure 20, s = secure 20 */
        || !TEST_true(CRYPTO_secure_allocated(s))
        /* 2 * 20 secure -> 64 bytes allocated */
        || !TEST_size_t_eq(CRYPTO_secure_used(), 64))
        goto end;
    OPENSSL_secure_clear_free(p, 20);
    p = NULL;
    /* 20 secure -> 32 bytes allocated */
    if (!TEST_size_t_eq(CRYPTO_secure_used(), 32))
        goto end;
    OPENSSL_free(q);
    q = NULL;
    /* should not complete, as secure memory is still allocated */
    if (!TEST_false(CRYPTO_secure_malloc_done())
        || !TEST_true(CRYPTO_secure_malloc_initialized()))
        goto end;
    OPENSSL_secure_free(s);
    s = NULL;
    /* secure memory should now be 0, so done should complete */
    if (!TEST_size_t_eq(CRYPTO_secure_used(), 0)
        || !TEST_true(CRYPTO_secure_malloc_done())
        || !TEST_false(CRYPTO_secure_malloc_initialized()))
        goto end;

    TEST_info("Possible infinite loop: allocate more than available");
    if (!TEST_true(CRYPTO_secure_malloc_init(32768, 16)))
        goto end;
    TEST_ptr_null(OPENSSL_secure_malloc((size_t)-1));
    TEST_true(CRYPTO_secure_malloc_done());

    /*
     * If init fails, then initialized should be false, if not, this
     * could cause an infinite loop secure_malloc, but we don't test it
     */
    if (TEST_false(CRYPTO_secure_malloc_init(16, 16)) &&
        !TEST_false(CRYPTO_secure_malloc_initialized())) {
        TEST_true(CRYPTO_secure_malloc_done());
        goto end;
    }

    /*-
     * There was also a possible infinite loop when the number of
     * elements was 1<<31, as |int i| was set to that, which is a
     * negative number. However, it requires minimum input values:
     *
     * CRYPTO_secure_malloc_init((size_t)1<<34, (size_t)1<<4);
     *
     * Which really only works on 64-bit systems, since it took 16 GB
     * secure memory arena to trigger the problem. It naturally takes
     * corresponding amount of available virtual and physical memory
     * for test to be feasible/representative. Since we can't assume
     * that every system is equipped with that much memory, the test
     * remains disabled. If the reader of this comment really wants
     * to make sure that infinite loop is fixed, they can enable the
     * code below.
     */
# if 0
    /*-
     * On Linux and BSD this test has a chance to complete in minimal
     * time and with minimum side effects, because mlock is likely to
     * fail because of RLIMIT_MEMLOCK, which is customarily [much]
     * smaller than 16GB. In other words Linux and BSD users can be
     * limited by virtual space alone...
     */
    if (sizeof(size_t) > 4) {
        TEST_info("Possible infinite loop: 1<<31 limit");
        if (TEST_true(CRYPTO_secure_malloc_init((size_t)1<<34, (size_t)1<<4) != 0))
            TEST_true(CRYPTO_secure_malloc_done());
    }
# endif

    /* this can complete - it was not really secure */
    testresult = 1;
 end:
    OPENSSL_secure_free(p);
    OPENSSL_free(q);
    OPENSSL_secure_free(r);
    OPENSSL_secure_free(s);
    return testresult;
#else
    TEST_info("Secure memory is *not* implemented.");
    /* Should fail. */
    return TEST_false(CRYPTO_secure_malloc_init(4096, 32));
#endif
}