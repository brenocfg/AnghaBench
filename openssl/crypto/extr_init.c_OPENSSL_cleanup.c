#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  (* handler ) () ;} ;
typedef  TYPE_1__ OPENSSL_INIT_STOP ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_secure_malloc_done () ; 
 int /*<<< orphan*/  INIT ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_thread_stop () ; 
 int /*<<< orphan*/  OSSL_CMP_log_close () ; 
 int /*<<< orphan*/  OSSL_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  async_deinit () ; 
 scalar_t__ async_inited ; 
 scalar_t__ base_inited ; 
 int /*<<< orphan*/  bio_cleanup () ; 
 int /*<<< orphan*/  comp_zlib_cleanup_int () ; 
 int /*<<< orphan*/  conf_modules_free_int () ; 
 int /*<<< orphan*/  engine_cleanup_int () ; 
 int /*<<< orphan*/  err_cleanup () ; 
 int /*<<< orphan*/  err_free_strings_int () ; 
 int /*<<< orphan*/  evp_cleanup_int () ; 
 int /*<<< orphan*/ * init_lock ; 
 scalar_t__ load_crypto_strings_inited ; 
 int /*<<< orphan*/  obj_cleanup_int () ; 
 int /*<<< orphan*/  openssl_ctx_default_deinit () ; 
 int /*<<< orphan*/  ossl_cleanup_thread () ; 
 int /*<<< orphan*/  ossl_store_cleanup_int () ; 
 int /*<<< orphan*/  ossl_trace_cleanup () ; 
 int /*<<< orphan*/  rand_cleanup_int () ; 
 TYPE_1__* stop_handlers ; 
 int stopped ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ zlib_inited ; 

void OPENSSL_cleanup(void)
{
    OPENSSL_INIT_STOP *currhandler, *lasthandler;

    /*
     * TODO(3.0): This function needs looking at with a view to moving most/all
     * of this into onfree handlers in OPENSSL_CTX.
     */

    /* If we've not been inited then no need to deinit */
    if (!base_inited)
        return;

    /* Might be explicitly called and also by atexit */
    if (stopped)
        return;
    stopped = 1;

    /*
     * Thread stop may not get automatically called by the thread library for
     * the very last thread in some situations, so call it directly.
     */
    OPENSSL_thread_stop();

    currhandler = stop_handlers;
    while (currhandler != NULL) {
        currhandler->handler();
        lasthandler = currhandler;
        currhandler = currhandler->next;
        OPENSSL_free(lasthandler);
    }
    stop_handlers = NULL;

    CRYPTO_THREAD_lock_free(init_lock);
    init_lock = NULL;

    /*
     * We assume we are single-threaded for this function, i.e. no race
     * conditions for the various "*_inited" vars below.
     */

#ifndef OPENSSL_NO_COMP
    if (zlib_inited) {
        OSSL_TRACE(INIT, "OPENSSL_cleanup: comp_zlib_cleanup_int()\n");
        comp_zlib_cleanup_int();
    }
#endif

    if (async_inited) {
        OSSL_TRACE(INIT, "OPENSSL_cleanup: async_deinit()\n");
        async_deinit();
    }

    if (load_crypto_strings_inited) {
        OSSL_TRACE(INIT, "OPENSSL_cleanup: err_free_strings_int()\n");
        err_free_strings_int();
    }

    /*
     * Note that cleanup order is important:
     * - rand_cleanup_int could call an ENGINE's RAND cleanup function so
     * must be called before engine_cleanup_int()
     * - ENGINEs use CRYPTO_EX_DATA and therefore, must be cleaned up
     * before the ex data handlers are wiped during default openssl_ctx deinit.
     * - conf_modules_free_int() can end up in ENGINE code so must be called
     * before engine_cleanup_int()
     * - ENGINEs and additional EVP algorithms might use added OIDs names so
     * obj_cleanup_int() must be called last
     */
    OSSL_TRACE(INIT, "OPENSSL_cleanup: rand_cleanup_int()\n");
    rand_cleanup_int();

    OSSL_TRACE(INIT, "OPENSSL_cleanup: conf_modules_free_int()\n");
    conf_modules_free_int();

#ifndef OPENSSL_NO_ENGINE
    OSSL_TRACE(INIT, "OPENSSL_cleanup: engine_cleanup_int()\n");
    engine_cleanup_int();
#endif
    OSSL_TRACE(INIT, "OPENSSL_cleanup: ossl_store_cleanup_int()\n");
    ossl_store_cleanup_int();

    OSSL_TRACE(INIT, "OPENSSL_cleanup: openssl_ctx_default_deinit()\n");
    openssl_ctx_default_deinit();

    ossl_cleanup_thread();

    OSSL_TRACE(INIT, "OPENSSL_cleanup: bio_cleanup()\n");
    bio_cleanup();

    OSSL_TRACE(INIT, "OPENSSL_cleanup: evp_cleanup_int()\n");
    evp_cleanup_int();

    OSSL_TRACE(INIT, "OPENSSL_cleanup: obj_cleanup_int()\n");
    obj_cleanup_int();

    OSSL_TRACE(INIT, "OPENSSL_cleanup: err_int()\n");
    err_cleanup();

    OSSL_TRACE(INIT, "OPENSSL_cleanup: CRYPTO_secure_malloc_done()\n");
    CRYPTO_secure_malloc_done();

#ifndef OPENSSL_NO_CMP
    OSSL_TRACE(INIT, "OPENSSL_cleanup: OSSL_CMP_log_close()\n");
    OSSL_CMP_log_close();
#endif

    OSSL_TRACE(INIT, "OPENSSL_cleanup: ossl_trace_cleanup()\n");
    ossl_trace_cleanup();

    base_inited = 0;
}