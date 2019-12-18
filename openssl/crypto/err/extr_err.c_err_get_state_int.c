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
 int /*<<< orphan*/ * CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_STATE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_INIT_BASE_ONLY ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_CRYPTO_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_delete_thread_state ; 
 int /*<<< orphan*/  err_do_init ; 
 int /*<<< orphan*/  err_init ; 
 int /*<<< orphan*/  err_thread_local ; 
 int get_last_sys_error () ; 
 int /*<<< orphan*/  ossl_init_thread_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sys_error (int) ; 

ERR_STATE *err_get_state_int(void)
{
    ERR_STATE *state;
    int saveerrno = get_last_sys_error();

    if (!OPENSSL_init_crypto(OPENSSL_INIT_BASE_ONLY, NULL))
        return NULL;

    if (!RUN_ONCE(&err_init, err_do_init))
        return NULL;

    state = CRYPTO_THREAD_get_local(&err_thread_local);
    if (state == (ERR_STATE*)-1)
        return NULL;

    if (state == NULL) {
        if (!CRYPTO_THREAD_set_local(&err_thread_local, (ERR_STATE*)-1))
            return NULL;

        if ((state = OPENSSL_zalloc(sizeof(*state))) == NULL) {
            CRYPTO_THREAD_set_local(&err_thread_local, NULL);
            return NULL;
        }

        if (!ossl_init_thread_start(NULL, NULL, err_delete_thread_state)
                || !CRYPTO_THREAD_set_local(&err_thread_local, state)) {
            ERR_STATE_free(state);
            CRYPTO_THREAD_set_local(&err_thread_local, NULL);
            return NULL;
        }

        /* Ignore failures from these */
        OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);
    }

    set_sys_error(saveerrno);
    return state;
}