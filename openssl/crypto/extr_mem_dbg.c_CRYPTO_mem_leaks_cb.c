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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int (* print_cb ) (char const*,size_t,void*) ;scalar_t__ chunks; scalar_t__ bytes; void* print_cb_arg; } ;
typedef  TYPE_1__ MEM_LEAK ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,scalar_t__,scalar_t__) ; 
 int CRYPTO_MEM_CHECK_DISABLE ; 
 int CRYPTO_MEM_CHECK_OFF ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_mem_ctrl (int) ; 
 int /*<<< orphan*/  OPENSSL_cleanup () ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_memdbg_init ; 
 int /*<<< orphan*/  lh_MEM_doall_MEM_LEAK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  lh_MEM_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * long_memdbg_lock ; 
 int /*<<< orphan*/  memdbg_init ; 
 int /*<<< orphan*/ * memdbg_lock ; 
 int /*<<< orphan*/ * mh ; 
 int mh_mode ; 
 int /*<<< orphan*/  print_leak ; 
 size_t strlen (char*) ; 

int CRYPTO_mem_leaks_cb(int (*cb) (const char *str, size_t len, void *u),
                        void *u)
{
    MEM_LEAK ml;

    /* Ensure all resources are released */
    OPENSSL_cleanup();

    if (!RUN_ONCE(&memdbg_init, do_memdbg_init))
        return -1;

    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_DISABLE);

    ml.print_cb = cb;
    ml.print_cb_arg = u;
    ml.bytes = 0;
    ml.chunks = 0;
    if (mh != NULL)
        lh_MEM_doall_MEM_LEAK(mh, print_leak, &ml);

    if (ml.chunks != 0) {
        char buf[256];

        BIO_snprintf(buf, sizeof(buf), "%ld bytes leaked in %d chunks\n",
                     ml.bytes, ml.chunks);
        cb(buf, strlen(buf), u);
    } else {
        /*
         * Make sure that, if we found no leaks, memory-leak debugging itself
         * does not introduce memory leaks (which might irritate external
         * debugging tools). (When someone enables leak checking, but does not
         * call this function, we declare it to be their fault.)
         */
        int old_mh_mode;

        CRYPTO_THREAD_write_lock(memdbg_lock);

        /*
         * avoid deadlock when lh_free() uses CRYPTO_mem_debug_free(), which uses
         * mem_check_on
         */
        old_mh_mode = mh_mode;
        mh_mode = CRYPTO_MEM_CHECK_OFF;

        lh_MEM_free(mh);
        mh = NULL;

        mh_mode = old_mh_mode;
        CRYPTO_THREAD_unlock(memdbg_lock);
    }
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_OFF);

    /* Clean up locks etc */
    CRYPTO_THREAD_lock_free(memdbg_lock);
    CRYPTO_THREAD_lock_free(long_memdbg_lock);
    memdbg_lock = NULL;
    long_memdbg_lock = NULL;

    return ml.chunks == 0 ? 1 : 0;
}