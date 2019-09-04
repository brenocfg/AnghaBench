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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  AFALG_F_BIND_AFALG ; 
 int /*<<< orphan*/  AFALG_R_INIT_FAILED ; 
 int /*<<< orphan*/  AFALGerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_ciphers (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_destroy_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_finish_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_init_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_load_AFALG_strings () ; 
 unsigned short OSSL_NELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * afalg_aes_cbc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * afalg_cipher_nids ; 
 int /*<<< orphan*/  afalg_ciphers ; 
 int /*<<< orphan*/  afalg_destroy ; 
 int /*<<< orphan*/  afalg_finish ; 
 int /*<<< orphan*/  afalg_init ; 
 int /*<<< orphan*/  engine_afalg_id ; 
 int /*<<< orphan*/  engine_afalg_name ; 

__attribute__((used)) static int bind_afalg(ENGINE *e)
{
    /* Ensure the afalg error handling is set up */
    unsigned short i;
    ERR_load_AFALG_strings();

    if (!ENGINE_set_id(e, engine_afalg_id)
        || !ENGINE_set_name(e, engine_afalg_name)
        || !ENGINE_set_destroy_function(e, afalg_destroy)
        || !ENGINE_set_init_function(e, afalg_init)
        || !ENGINE_set_finish_function(e, afalg_finish)) {
        AFALGerr(AFALG_F_BIND_AFALG, AFALG_R_INIT_FAILED);
        return 0;
    }

    /*
     * Create _hidden_aes_xxx_cbc by calling afalg_aes_xxx_cbc
     * now, as bind_aflag can only be called by one thread at a
     * time.
     */
    for(i = 0; i < OSSL_NELEM(afalg_cipher_nids); i++) {
        if (afalg_aes_cbc(afalg_cipher_nids[i]) == NULL) {
            AFALGerr(AFALG_F_BIND_AFALG, AFALG_R_INIT_FAILED);
            return 0;
        }
    }

    if (!ENGINE_set_ciphers(e, afalg_ciphers)) {
        AFALGerr(AFALG_F_BIND_AFALG, AFALG_R_INIT_FAILED);
        return 0;
    }

    return 1;
}