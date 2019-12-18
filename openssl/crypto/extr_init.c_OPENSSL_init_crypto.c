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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  OPENSSL_INIT_SETTINGS ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_OPENSSL_INIT_CRYPTO ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_register_all_complete () ; 
 int /*<<< orphan*/  ERR_R_INIT_FAIL ; 
 int OPENSSL_INIT_ADD_ALL_CIPHERS ; 
 int OPENSSL_INIT_ADD_ALL_DIGESTS ; 
 int OPENSSL_INIT_ASYNC ; 
 int OPENSSL_INIT_ATFORK ; 
 int OPENSSL_INIT_BASE_ONLY ; 
 int OPENSSL_INIT_ENGINE_AFALG ; 
 int OPENSSL_INIT_ENGINE_ALL_BUILTIN ; 
 int OPENSSL_INIT_ENGINE_CAPI ; 
 int OPENSSL_INIT_ENGINE_CRYPTODEV ; 
 int OPENSSL_INIT_ENGINE_DYNAMIC ; 
 int OPENSSL_INIT_ENGINE_OPENSSL ; 
 int OPENSSL_INIT_ENGINE_PADLOCK ; 
 int OPENSSL_INIT_ENGINE_RDRAND ; 
 int OPENSSL_INIT_LOAD_CONFIG ; 
 int OPENSSL_INIT_LOAD_CRYPTO_STRINGS ; 
 int OPENSSL_INIT_NO_ADD_ALL_CIPHERS ; 
 int OPENSSL_INIT_NO_ADD_ALL_DIGESTS ; 
 int OPENSSL_INIT_NO_ATEXIT ; 
 int OPENSSL_INIT_NO_LOAD_CONFIG ; 
 int OPENSSL_INIT_NO_LOAD_CRYPTO_STRINGS ; 
 int OPENSSL_INIT_ZLIB ; 
 int RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_ONCE_ALT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_all_ciphers ; 
 int /*<<< orphan*/  add_all_digests ; 
 int /*<<< orphan*/  async ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  const* conf_settings ; 
 int /*<<< orphan*/  config ; 
 int /*<<< orphan*/  engine_afalg ; 
 int /*<<< orphan*/  engine_capi ; 
 int /*<<< orphan*/  engine_devcrypto ; 
 int /*<<< orphan*/  engine_dynamic ; 
 int /*<<< orphan*/  engine_openssl ; 
 int /*<<< orphan*/  engine_padlock ; 
 int /*<<< orphan*/  engine_rdrand ; 
 int /*<<< orphan*/  init_lock ; 
 int /*<<< orphan*/  load_crypto_nodelete ; 
 int /*<<< orphan*/  load_crypto_strings ; 
 int /*<<< orphan*/  openssl_init_fork_handlers () ; 
 int /*<<< orphan*/  ossl_init_add_all_ciphers ; 
 int /*<<< orphan*/  ossl_init_add_all_digests ; 
 int /*<<< orphan*/  ossl_init_async ; 
 int /*<<< orphan*/  ossl_init_base ; 
 int /*<<< orphan*/  ossl_init_config ; 
 int /*<<< orphan*/  ossl_init_engine_afalg ; 
 int /*<<< orphan*/  ossl_init_engine_capi ; 
 int /*<<< orphan*/  ossl_init_engine_devcrypto ; 
 int /*<<< orphan*/  ossl_init_engine_dynamic ; 
 int /*<<< orphan*/  ossl_init_engine_openssl ; 
 int /*<<< orphan*/  ossl_init_engine_padlock ; 
 int /*<<< orphan*/  ossl_init_engine_rdrand ; 
 int /*<<< orphan*/  ossl_init_load_crypto_nodelete ; 
 int /*<<< orphan*/  ossl_init_load_crypto_strings ; 
 int /*<<< orphan*/  ossl_init_no_add_all_ciphers ; 
 int /*<<< orphan*/  ossl_init_no_add_all_digests ; 
 int /*<<< orphan*/  ossl_init_no_config ; 
 int /*<<< orphan*/  ossl_init_no_load_crypto_strings ; 
 int /*<<< orphan*/  ossl_init_no_register_atexit ; 
 int /*<<< orphan*/  ossl_init_register_atexit ; 
 int /*<<< orphan*/  ossl_init_zlib ; 
 int /*<<< orphan*/  register_atexit ; 
 scalar_t__ stopped ; 
 int /*<<< orphan*/  zlib ; 

int OPENSSL_init_crypto(uint64_t opts, const OPENSSL_INIT_SETTINGS *settings)
{
    /*
     * TODO(3.0): This function needs looking at with a view to moving most/all
     * of this into OPENSSL_CTX.
     */

    if (stopped) {
        if (!(opts & OPENSSL_INIT_BASE_ONLY))
            CRYPTOerr(CRYPTO_F_OPENSSL_INIT_CRYPTO, ERR_R_INIT_FAIL);
        return 0;
    }

    /*
     * When the caller specifies OPENSSL_INIT_BASE_ONLY, that should be the
     * *only* option specified.  With that option we return immediately after
     * doing the requested limited initialization.  Note that
     * err_shelve_state() called by us via ossl_init_load_crypto_nodelete()
     * re-enters OPENSSL_init_crypto() with OPENSSL_INIT_BASE_ONLY, but with
     * base already initialized this is a harmless NOOP.
     *
     * If we remain the only caller of err_shelve_state() the recursion should
     * perhaps be removed, but if in doubt, it can be left in place.
     */
    if (!RUN_ONCE(&base, ossl_init_base))
        return 0;

    if (opts & OPENSSL_INIT_BASE_ONLY)
        return 1;

    /*
     * Now we don't always set up exit handlers, the INIT_BASE_ONLY calls
     * should not have the side-effect of setting up exit handlers, and
     * therefore, this code block is below the INIT_BASE_ONLY-conditioned early
     * return above.
     */
    if ((opts & OPENSSL_INIT_NO_ATEXIT) != 0) {
        if (!RUN_ONCE_ALT(&register_atexit, ossl_init_no_register_atexit,
                          ossl_init_register_atexit))
            return 0;
    } else if (!RUN_ONCE(&register_atexit, ossl_init_register_atexit)) {
        return 0;
    }

    if (!RUN_ONCE(&load_crypto_nodelete, ossl_init_load_crypto_nodelete))
        return 0;

    if ((opts & OPENSSL_INIT_NO_LOAD_CRYPTO_STRINGS)
            && !RUN_ONCE_ALT(&load_crypto_strings,
                             ossl_init_no_load_crypto_strings,
                             ossl_init_load_crypto_strings))
        return 0;

    if ((opts & OPENSSL_INIT_LOAD_CRYPTO_STRINGS)
            && !RUN_ONCE(&load_crypto_strings, ossl_init_load_crypto_strings))
        return 0;

    if ((opts & OPENSSL_INIT_NO_ADD_ALL_CIPHERS)
            && !RUN_ONCE_ALT(&add_all_ciphers, ossl_init_no_add_all_ciphers,
                             ossl_init_add_all_ciphers))
        return 0;

    if ((opts & OPENSSL_INIT_ADD_ALL_CIPHERS)
            && !RUN_ONCE(&add_all_ciphers, ossl_init_add_all_ciphers))
        return 0;

    if ((opts & OPENSSL_INIT_NO_ADD_ALL_DIGESTS)
            && !RUN_ONCE_ALT(&add_all_digests, ossl_init_no_add_all_digests,
                             ossl_init_add_all_digests))
        return 0;

    if ((opts & OPENSSL_INIT_ADD_ALL_DIGESTS)
            && !RUN_ONCE(&add_all_digests, ossl_init_add_all_digests))
        return 0;

    if ((opts & OPENSSL_INIT_ATFORK)
            && !openssl_init_fork_handlers())
        return 0;

    if ((opts & OPENSSL_INIT_NO_LOAD_CONFIG)
            && !RUN_ONCE_ALT(&config, ossl_init_no_config, ossl_init_config))
        return 0;

    if (opts & OPENSSL_INIT_LOAD_CONFIG) {
        int ret;
        CRYPTO_THREAD_write_lock(init_lock);
        conf_settings = settings;
        ret = RUN_ONCE(&config, ossl_init_config);
        conf_settings = NULL;
        CRYPTO_THREAD_unlock(init_lock);
        if (ret <= 0)
            return 0;
    }

    if ((opts & OPENSSL_INIT_ASYNC)
            && !RUN_ONCE(&async, ossl_init_async))
        return 0;

#ifndef OPENSSL_NO_ENGINE
    if ((opts & OPENSSL_INIT_ENGINE_OPENSSL)
            && !RUN_ONCE(&engine_openssl, ossl_init_engine_openssl))
        return 0;
# ifndef OPENSSL_NO_RDRAND
    if ((opts & OPENSSL_INIT_ENGINE_RDRAND)
            && !RUN_ONCE(&engine_rdrand, ossl_init_engine_rdrand))
        return 0;
# endif
    if ((opts & OPENSSL_INIT_ENGINE_DYNAMIC)
            && !RUN_ONCE(&engine_dynamic, ossl_init_engine_dynamic))
        return 0;
# ifndef OPENSSL_NO_STATIC_ENGINE
#  ifndef OPENSSL_NO_DEVCRYPTOENG
    if ((opts & OPENSSL_INIT_ENGINE_CRYPTODEV)
            && !RUN_ONCE(&engine_devcrypto, ossl_init_engine_devcrypto))
        return 0;
#  endif
#  if !defined(OPENSSL_NO_PADLOCKENG)
    if ((opts & OPENSSL_INIT_ENGINE_PADLOCK)
            && !RUN_ONCE(&engine_padlock, ossl_init_engine_padlock))
        return 0;
#  endif
#  if defined(OPENSSL_SYS_WIN32) && !defined(OPENSSL_NO_CAPIENG)
    if ((opts & OPENSSL_INIT_ENGINE_CAPI)
            && !RUN_ONCE(&engine_capi, ossl_init_engine_capi))
        return 0;
#  endif
#  if !defined(OPENSSL_NO_AFALGENG)
    if ((opts & OPENSSL_INIT_ENGINE_AFALG)
            && !RUN_ONCE(&engine_afalg, ossl_init_engine_afalg))
        return 0;
#  endif
# endif
    if (opts & (OPENSSL_INIT_ENGINE_ALL_BUILTIN
                | OPENSSL_INIT_ENGINE_OPENSSL
                | OPENSSL_INIT_ENGINE_AFALG)) {
        ENGINE_register_all_complete();
    }
#endif

#ifndef OPENSSL_NO_COMP
    if ((opts & OPENSSL_INIT_ZLIB)
            && !RUN_ONCE(&zlib, ossl_init_zlib))
        return 0;
#endif

    return 1;
}