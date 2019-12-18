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
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  int /*<<< orphan*/  EVP_MAC ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 char* ENGINE_get_id (int /*<<< orphan*/ *) ; 
 char* EVP_CIPHER_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_CIPHER_provider (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_F_EVP_PKEY_NEW_CMAC_KEY ; 
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MAC_CTX_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MAC_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CMAC ; 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_2__*) ; 
 TYPE_2__* EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_R_KEY_SETUP_FAILED ; 
 int /*<<< orphan*/  EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_MAC_NAME_CMAC ; 
 char* OSSL_MAC_PARAM_CIPHER ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ossl_provider_library_context (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pkey_set_type (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

EVP_PKEY *EVP_PKEY_new_CMAC_key(ENGINE *e, const unsigned char *priv,
                                size_t len, const EVP_CIPHER *cipher)
{
#ifndef OPENSSL_NO_CMAC
# ifndef OPENSSL_NO_ENGINE
    const char *engine_id = e != NULL ? ENGINE_get_id(e) : NULL;
# endif
    const char *cipher_name = EVP_CIPHER_name(cipher);
    const OSSL_PROVIDER *prov = EVP_CIPHER_provider(cipher);
    OPENSSL_CTX *libctx =
        prov == NULL ? NULL : ossl_provider_library_context(prov);
    EVP_PKEY *ret = EVP_PKEY_new();
    EVP_MAC *cmac = EVP_MAC_fetch(libctx, OSSL_MAC_NAME_CMAC, NULL);
    EVP_MAC_CTX *cmctx = cmac != NULL ? EVP_MAC_CTX_new(cmac) : NULL;
    OSSL_PARAM params[4];
    size_t paramsn = 0;

    if (ret == NULL
            || cmctx == NULL
            || !pkey_set_type(ret, e, EVP_PKEY_CMAC, NULL, -1)) {
        /* EVPerr already called */
        goto err;
    }

# ifndef OPENSSL_NO_ENGINE
    if (engine_id != NULL)
        params[paramsn++] =
            OSSL_PARAM_construct_utf8_string("engine", (char *)engine_id, 0);
# endif

    params[paramsn++] =
        OSSL_PARAM_construct_utf8_string(OSSL_MAC_PARAM_CIPHER,
                                         (char *)cipher_name, 0);
    params[paramsn++] =
        OSSL_PARAM_construct_octet_string(OSSL_MAC_PARAM_KEY,
                                          (char *)priv, len);
    params[paramsn] = OSSL_PARAM_construct_end();

    if (!EVP_MAC_CTX_set_params(cmctx, params)) {
        EVPerr(EVP_F_EVP_PKEY_NEW_CMAC_KEY, EVP_R_KEY_SETUP_FAILED);
        goto err;
    }

    ret->pkey.ptr = cmctx;
    return ret;

 err:
    EVP_PKEY_free(ret);
    EVP_MAC_CTX_free(cmctx);
    EVP_MAC_free(cmac);
    return NULL;
#else
    EVPerr(EVP_F_EVP_PKEY_NEW_CMAC_KEY,
           EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
    return NULL;
#endif
}