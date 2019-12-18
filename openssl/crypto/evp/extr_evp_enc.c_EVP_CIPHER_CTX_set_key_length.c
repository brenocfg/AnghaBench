#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {int key_len; TYPE_2__* cipher; int /*<<< orphan*/  provctx; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_1__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_ctrl (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_CTX_key_length (TYPE_1__*) ; 
 int EVP_CIPH_CUSTOM_KEY_LENGTH ; 
 int EVP_CIPH_VARIABLE_LENGTH ; 
 int EVP_CTRL_RET_UNSUPPORTED ; 
 int /*<<< orphan*/  EVP_CTRL_SET_KEY_LENGTH ; 
 int /*<<< orphan*/  EVP_F_EVP_CIPHER_CTX_SET_KEY_LENGTH ; 
 int /*<<< orphan*/  EVP_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_KEYLEN ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_size_t (int /*<<< orphan*/ ,size_t*) ; 
 int evp_do_ciph_ctx_setparams (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int EVP_CIPHER_CTX_set_key_length(EVP_CIPHER_CTX *c, int keylen)
{
    int ok;
    OSSL_PARAM params[2] = { OSSL_PARAM_END, OSSL_PARAM_END };
    size_t len = keylen;

    params[0] = OSSL_PARAM_construct_size_t(OSSL_CIPHER_PARAM_KEYLEN, &len);
    ok = evp_do_ciph_ctx_setparams(c->cipher, c->provctx, params);

    if (ok != EVP_CTRL_RET_UNSUPPORTED)
        return ok;

    /* TODO(3.0) legacy code follows */
    if (c->cipher->flags & EVP_CIPH_CUSTOM_KEY_LENGTH)
        return EVP_CIPHER_CTX_ctrl(c, EVP_CTRL_SET_KEY_LENGTH, keylen, NULL);
    if (EVP_CIPHER_CTX_key_length(c) == keylen)
        return 1;
    if ((keylen > 0) && (c->cipher->flags & EVP_CIPH_VARIABLE_LENGTH)) {
        c->key_len = keylen;
        return 1;
    }
    EVPerr(EVP_F_EVP_CIPHER_CTX_SET_KEY_LENGTH, EVP_R_INVALID_KEY_LENGTH);
    return 0;
}