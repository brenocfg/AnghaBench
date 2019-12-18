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
struct TYPE_4__ {size_t block_size; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_1__ EVP_CIPHER ;

/* Variables and functions */
 int EVP_CTRL_RET_UNSUPPORTED ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_BLOCK_SIZE ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_size_t (int /*<<< orphan*/ ,size_t*) ; 
 int evp_do_ciph_getparams (TYPE_1__ const*,int /*<<< orphan*/ *) ; 

int EVP_CIPHER_block_size(const EVP_CIPHER *cipher)
{
    int ok;
    size_t v = cipher->block_size;
    OSSL_PARAM params[2] = { OSSL_PARAM_END, OSSL_PARAM_END };

    params[0] = OSSL_PARAM_construct_size_t(OSSL_CIPHER_PARAM_BLOCK_SIZE, &v);
    ok = evp_do_ciph_getparams(cipher, params);

    return ok != 0 ? (int)v : EVP_CTRL_RET_UNSUPPORTED;
}