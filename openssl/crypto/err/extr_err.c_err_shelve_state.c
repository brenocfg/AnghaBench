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
typedef  int /*<<< orphan*/  ERR_STATE ;

/* Variables and functions */
 void* CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_INIT_BASE_ONLY ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_do_init ; 
 int /*<<< orphan*/  err_init ; 
 int /*<<< orphan*/  err_thread_local ; 
 int get_last_sys_error () ; 
 int /*<<< orphan*/  set_sys_error (int) ; 

int err_shelve_state(void **state)
{
    int saveerrno = get_last_sys_error();

    /*
     * Note, at present our only caller is OPENSSL_init_crypto(), indirectly
     * via ossl_init_load_crypto_nodelete(), by which point the requested
     * "base" initialization has already been performed, so the below call is a
     * NOOP, that re-enters OPENSSL_init_crypto() only to quickly return.
     *
     * If are no other valid callers of this function, the call below can be
     * removed, avoiding the re-entry into OPENSSL_init_crypto().  If there are
     * potential uses that are not from inside OPENSSL_init_crypto(), then this
     * call is needed, but some care is required to make sure that the re-entry
     * remains a NOOP.
     */
    if (!OPENSSL_init_crypto(OPENSSL_INIT_BASE_ONLY, NULL))
        return 0;

    if (!RUN_ONCE(&err_init, err_do_init))
        return 0;

    *state = CRYPTO_THREAD_get_local(&err_thread_local);
    if (!CRYPTO_THREAD_set_local(&err_thread_local, (ERR_STATE*)-1))
        return 0;

    set_sys_error(saveerrno);
    return 1;
}