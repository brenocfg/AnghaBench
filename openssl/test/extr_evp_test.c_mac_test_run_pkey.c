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
struct TYPE_7__ {char* err; TYPE_1__* data; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  output_len; int /*<<< orphan*/  output; int /*<<< orphan*/  input_len; int /*<<< orphan*/  input; int /*<<< orphan*/  controls; int /*<<< orphan*/ * alg; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ MAC_DATA ;
typedef  TYPE_2__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  unsigned char EVP_MD_CTX ;
typedef  unsigned char EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestSignFinal (unsigned char*,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  EVP_DigestSignInit (unsigned char*,int /*<<< orphan*/ **,unsigned char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestSignUpdate (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (unsigned char*) ; 
 unsigned char* EVP_MD_CTX_new () ; 
 scalar_t__ EVP_PKEY_CMAC ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_HMAC ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new_CMAC_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_PKEY_new_raw_private_key (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_get_cipherbyname (int /*<<< orphan*/ *) ; 
 unsigned char* EVP_get_digestbyname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_nid2sn (scalar_t__) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char const*) ; 
 int /*<<< orphan*/  mac_test_ctrl_pkey (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_err_compare (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int sk_OPENSSL_STRING_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_OPENSSL_STRING_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mac_test_run_pkey(EVP_TEST *t)
{
    MAC_DATA *expected = t->data;
    EVP_MD_CTX *mctx = NULL;
    EVP_PKEY_CTX *pctx = NULL, *genctx = NULL;
    EVP_PKEY *key = NULL;
    const EVP_MD *md = NULL;
    unsigned char *got = NULL;
    size_t got_len;
    int i;

    if (expected->alg == NULL)
        TEST_info("Trying the EVP_PKEY %s test", OBJ_nid2sn(expected->type));
    else
        TEST_info("Trying the EVP_PKEY %s test with %s",
                  OBJ_nid2sn(expected->type), expected->alg);

#ifdef OPENSSL_NO_DES
    if (expected->alg != NULL && strstr(expected->alg, "DES") != NULL) {
        /* Skip DES */
        t->err = NULL;
        goto err;
    }
#endif

    if (expected->type == EVP_PKEY_CMAC)
        key = EVP_PKEY_new_CMAC_key(NULL, expected->key, expected->key_len,
                                    EVP_get_cipherbyname(expected->alg));
    else
        key = EVP_PKEY_new_raw_private_key(expected->type, NULL, expected->key,
                                           expected->key_len);
    if (key == NULL) {
        t->err = "MAC_KEY_CREATE_ERROR";
        goto err;
    }

    if (expected->type == EVP_PKEY_HMAC) {
        if (!TEST_ptr(md = EVP_get_digestbyname(expected->alg))) {
            t->err = "MAC_ALGORITHM_SET_ERROR";
            goto err;
        }
    }
    if (!TEST_ptr(mctx = EVP_MD_CTX_new())) {
        t->err = "INTERNAL_ERROR";
        goto err;
    }
    if (!EVP_DigestSignInit(mctx, &pctx, md, NULL, key)) {
        t->err = "DIGESTSIGNINIT_ERROR";
        goto err;
    }
    for (i = 0; i < sk_OPENSSL_STRING_num(expected->controls); i++)
        if (!mac_test_ctrl_pkey(t, pctx,
                                sk_OPENSSL_STRING_value(expected->controls,
                                                        i))) {
            t->err = "EVPPKEYCTXCTRL_ERROR";
            goto err;
        }
    if (!EVP_DigestSignUpdate(mctx, expected->input, expected->input_len)) {
        t->err = "DIGESTSIGNUPDATE_ERROR";
        goto err;
    }
    if (!EVP_DigestSignFinal(mctx, NULL, &got_len)) {
        t->err = "DIGESTSIGNFINAL_LENGTH_ERROR";
        goto err;
    }
    if (!TEST_ptr(got = OPENSSL_malloc(got_len))) {
        t->err = "TEST_FAILURE";
        goto err;
    }
    if (!EVP_DigestSignFinal(mctx, got, &got_len)
            || !memory_err_compare(t, "TEST_MAC_ERR",
                                   expected->output, expected->output_len,
                                   got, got_len)) {
        t->err = "TEST_MAC_ERR";
        goto err;
    }
    t->err = NULL;
 err:
    EVP_MD_CTX_free(mctx);
    OPENSSL_free(got);
    EVP_PKEY_CTX_free(genctx);
    EVP_PKEY_free(key);
    return 1;
}