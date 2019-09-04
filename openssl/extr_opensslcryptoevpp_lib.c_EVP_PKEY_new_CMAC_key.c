#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_8__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_NEW_CMAC_KEY ; 
 int /*<<< orphan*/  EVP_MAC_CMAC ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_CIPHER ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_ENGINE ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MAC_CTX_new_id (int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_MAC_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,...) ; 
 int /*<<< orphan*/  EVP_PKEY_CMAC ; 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_2__*) ; 
 TYPE_2__* EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_R_KEY_SETUP_FAILED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_set_type (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

EVP_PKEY *EVP_PKEY_new_CMAC_key(ENGINE *e, const unsigned char *priv,
                                size_t len, const EVP_CIPHER *cipher)
{
#ifndef OPENSSL_NO_CMAC
    EVP_PKEY *ret = EVP_PKEY_new();
    EVP_MAC_CTX *cmctx = EVP_MAC_CTX_new_id(EVP_MAC_CMAC);

    if (ret == NULL
            || cmctx == NULL
            || !pkey_set_type(ret, e, EVP_PKEY_CMAC, NULL, -1)) {
        /* EVPerr already called */
        goto err;
    }

    if (EVP_MAC_ctrl(cmctx, EVP_MAC_CTRL_SET_ENGINE, e) <= 0
        || EVP_MAC_ctrl(cmctx, EVP_MAC_CTRL_SET_CIPHER, cipher) <= 0
        || EVP_MAC_ctrl(cmctx, EVP_MAC_CTRL_SET_KEY, priv, len) <= 0) {
        EVPerr(EVP_F_EVP_PKEY_NEW_CMAC_KEY, EVP_R_KEY_SETUP_FAILED);
        goto err;
    }

    ret->pkey.ptr = cmctx;
    return ret;

 err:
    EVP_PKEY_free(ret);
    EVP_MAC_CTX_free(cmctx);
    return NULL;
#else
    EVPerr(EVP_F_EVP_PKEY_NEW_CMAC_KEY,
           EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
    return NULL;
#endif
}