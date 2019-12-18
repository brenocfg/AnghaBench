#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  rand_add_buf ;
struct TYPE_25__ {int fail; } ;
struct TYPE_24__ {int /*<<< orphan*/  reseed_prop_counter; int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 TYPE_1__* RAND_DRBG_get0_master () ; 
 TYPE_1__* RAND_DRBG_get0_private () ; 
 TYPE_1__* RAND_DRBG_get0_public () ; 
 int /*<<< orphan*/  RAND_DRBG_uninstantiate (TYPE_1__*) ; 
 TYPE_1__* RAND_OpenSSL () ; 
 int /*<<< orphan*/  RAND_add (unsigned char*,int,int) ; 
 int /*<<< orphan*/  RAND_get_rand_method () ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_ptr_eq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_ptr_ne (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_crngt (TYPE_1__*) ; 
 int /*<<< orphan*/  hook_drbg (TYPE_1__*,TYPE_9__*) ; 
 TYPE_9__ master_ctx ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 TYPE_9__ private_ctx ; 
 TYPE_9__ public_ctx ; 
 int /*<<< orphan*/  reset_drbg_hook_ctx () ; 
 int /*<<< orphan*/  test_drbg_reseed (int,TYPE_1__*,TYPE_1__*,TYPE_1__*,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  test_drbg_reseed_after_fork (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unhook_drbg (TYPE_1__*) ; 

__attribute__((used)) static int test_rand_drbg_reseed(void)
{
    RAND_DRBG *master, *public, *private;
    unsigned char rand_add_buf[256];
    int rv=0;
    time_t before_reseed;

    /* Check whether RAND_OpenSSL() is the default method */
    if (!TEST_ptr_eq(RAND_get_rand_method(), RAND_OpenSSL()))
        return 0;

    /* All three DRBGs should be non-null */
    if (!TEST_ptr(master = RAND_DRBG_get0_master())
        || !TEST_ptr(public = RAND_DRBG_get0_public())
        || !TEST_ptr(private = RAND_DRBG_get0_private()))
        return 0;

    /* There should be three distinct DRBGs, two of them chained to master */
    if (!TEST_ptr_ne(public, private)
        || !TEST_ptr_ne(public, master)
        || !TEST_ptr_ne(private, master)
        || !TEST_ptr_eq(public->parent, master)
        || !TEST_ptr_eq(private->parent, master))
        return 0;

    /* Disable CRNG testing for the master DRBG */
    if (!TEST_true(disable_crngt(master)))
        return 0;

    /* uninstantiate the three global DRBGs */
    RAND_DRBG_uninstantiate(private);
    RAND_DRBG_uninstantiate(public);
    RAND_DRBG_uninstantiate(master);


    /* Install hooks for the following tests */
    hook_drbg(master,  &master_ctx);
    hook_drbg(public,  &public_ctx);
    hook_drbg(private, &private_ctx);


    /*
     * Test initial seeding of shared DRBGs
     */
    if (!TEST_true(test_drbg_reseed(1, master, public, private, 1, 1, 1, 0)))
        goto error;
    reset_drbg_hook_ctx();


    /*
     * Test initial state of shared DRBGs
     */
    if (!TEST_true(test_drbg_reseed(1, master, public, private, 0, 0, 0, 0)))
        goto error;
    reset_drbg_hook_ctx();

    /*
     * Test whether the public and private DRBG are both reseeded when their
     * reseed counters differ from the master's reseed counter.
     */
    master->reseed_prop_counter++;
    if (!TEST_true(test_drbg_reseed(1, master, public, private, 0, 1, 1, 0)))
        goto error;
    reset_drbg_hook_ctx();

    /*
     * Test whether the public DRBG is reseeded when its reseed counter differs
     * from the master's reseed counter.
     */
    master->reseed_prop_counter++;
    private->reseed_prop_counter++;
    if (!TEST_true(test_drbg_reseed(1, master, public, private, 0, 1, 0, 0)))
        goto error;
    reset_drbg_hook_ctx();

    /*
     * Test whether the private DRBG is reseeded when its reseed counter differs
     * from the master's reseed counter.
     */
    master->reseed_prop_counter++;
    public->reseed_prop_counter++;
    if (!TEST_true(test_drbg_reseed(1, master, public, private, 0, 0, 1, 0)))
        goto error;
    reset_drbg_hook_ctx();

#if defined(OPENSSL_SYS_UNIX)
    if (!TEST_true(test_drbg_reseed_after_fork(master, public, private)))
        goto error;
#endif

    /* fill 'randomness' buffer with some arbitrary data */
    memset(rand_add_buf, 'r', sizeof(rand_add_buf));

#ifndef FIPS_MODE
    /*
     * Test whether all three DRBGs are reseeded by RAND_add().
     * The before_reseed time has to be measured here and passed into the
     * test_drbg_reseed() test, because the master DRBG gets already reseeded
     * in RAND_add(), whence the check for the condition
     * before_reseed <= master->reseed_time will fail if the time value happens
     * to increase between the RAND_add() and the test_drbg_reseed() call.
     */
    before_reseed = time(NULL);
    RAND_add(rand_add_buf, sizeof(rand_add_buf), sizeof(rand_add_buf));
    if (!TEST_true(test_drbg_reseed(1, master, public, private, 1, 1, 1,
                                    before_reseed)))
        goto error;
    reset_drbg_hook_ctx();


    /*
     * Test whether none of the DRBGs is reseed if the master fails to reseed
     */
    master_ctx.fail = 1;
    master->reseed_prop_counter++;
    RAND_add(rand_add_buf, sizeof(rand_add_buf), sizeof(rand_add_buf));
    if (!TEST_true(test_drbg_reseed(0, master, public, private, 0, 0, 0, 0)))
        goto error;
    reset_drbg_hook_ctx();
#else /* FIPS_MODE */
    /*
     * In FIPS mode, random data provided by the application via RAND_add()
     * is not considered a trusted entropy source. It is only treated as
     * additional_data and no reseeding is forced. This test assures that
     * no reseeding occurs.
     */
    before_reseed = time(NULL);
    RAND_add(rand_add_buf, sizeof(rand_add_buf), sizeof(rand_add_buf));
    if (!TEST_true(test_drbg_reseed(1, master, public, private, 0, 0, 0,
                                    before_reseed)))
        goto error;
    reset_drbg_hook_ctx();
#endif

    rv = 1;

error:
    /* Remove hooks  */
    unhook_drbg(master);
    unhook_drbg(public);
    unhook_drbg(private);

    return rv;
}