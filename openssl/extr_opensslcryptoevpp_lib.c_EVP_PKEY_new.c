#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int references; int save_parameters; int /*<<< orphan*/ * lock; void* save_type; void* type; } ;
typedef  TYPE_1__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_PKEY_NEW ; 
 void* EVP_PKEY_NONE ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

EVP_PKEY *EVP_PKEY_new(void)
{
    EVP_PKEY *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL) {
        EVPerr(EVP_F_EVP_PKEY_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->type = EVP_PKEY_NONE;
    ret->save_type = EVP_PKEY_NONE;
    ret->references = 1;
    ret->save_parameters = 1;
    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        EVPerr(EVP_F_EVP_PKEY_NEW, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ret);
        return NULL;
    }
    return ret;
}