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
struct TYPE_3__ {int /*<<< orphan*/ * ex_data; int /*<<< orphan*/ * ex_data_lock; } ;
typedef  TYPE_1__ OSSL_EX_DATA_GLOBAL ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EX_CALLBACKS ;

/* Variables and functions */
 int CRYPTO_EX_INDEX__COUNT ; 
 int /*<<< orphan*/  CRYPTO_F_GET_AND_LOCK ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_INVALID_ARGUMENT ; 
 TYPE_1__* openssl_ctx_get_ex_data_global (int /*<<< orphan*/ *) ; 

__attribute__((used)) static EX_CALLBACKS *get_and_lock(OPENSSL_CTX *ctx, int class_index)
{
    EX_CALLBACKS *ip;
    OSSL_EX_DATA_GLOBAL *global = NULL;

    if (class_index < 0 || class_index >= CRYPTO_EX_INDEX__COUNT) {
        CRYPTOerr(CRYPTO_F_GET_AND_LOCK, ERR_R_PASSED_INVALID_ARGUMENT);
        return NULL;
    }

    global = openssl_ctx_get_ex_data_global(ctx);
    if (global == NULL || global->ex_data_lock == NULL) {
        /*
         * This can happen in normal operation when using CRYPTO_mem_leaks().
         * The CRYPTO_mem_leaks() function calls OPENSSL_cleanup() which cleans
         * up the locks. Subsequently the BIO that CRYPTO_mem_leaks() uses gets
         * freed, which also attempts to free the ex_data. However
         * CRYPTO_mem_leaks() ensures that the ex_data is freed early (i.e.
         * before OPENSSL_cleanup() is called), so if we get here we can safely
         * ignore this operation. We just treat it as an error.
         */
         return NULL;
    }

    CRYPTO_THREAD_write_lock(global->ex_data_lock);
    ip = &global->ex_data[class_index];
    return ip;
}