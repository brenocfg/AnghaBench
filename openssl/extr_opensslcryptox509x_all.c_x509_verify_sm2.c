#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ type; int flags; scalar_t__ length; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {TYPE_3__ signature; int /*<<< orphan*/  cert_info; TYPE_2__* sm2_id; } ;
typedef  TYPE_4__ X509 ;
struct TYPE_15__ {TYPE_1__* ameth; } ;
struct TYPE_12__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {scalar_t__ pkey_id; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  TYPE_5__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_R_INVALID_BIT_STRING_BITS_LEFT ; 
 int /*<<< orphan*/  ASN1_R_UNKNOWN_MESSAGE_DIGEST_ALGORITHM ; 
 int /*<<< orphan*/  ASN1_R_WRONG_PUBLIC_KEY_TYPE ; 
 int ASN1_item_i2d (int /*<<< orphan*/ *,unsigned char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int EVP_DigestVerify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_pkey_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_CTX_set1_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_SM2 ; 
 int /*<<< orphan*/  EVP_PKEY_set_alias_type (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_type (int) ; 
 int /*<<< orphan*/ * EVP_get_digestbynid (int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 scalar_t__ V_ASN1_BIT_STRING ; 
 int /*<<< orphan*/  X509_CINF ; 
 int /*<<< orphan*/  X509_F_X509_VERIFY_SM2 ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x509_verify_sm2(X509 *x, EVP_PKEY *pkey, int mdnid, int pknid)
{
    EVP_MD_CTX *ctx = NULL;
    unsigned char *buf_in = NULL;
    int ret = -1, inl = 0;
    size_t inll = 0;
    EVP_PKEY_CTX *pctx = NULL;
    const EVP_MD *type = EVP_get_digestbynid(mdnid);

    if (type == NULL) {
        X509err(X509_F_X509_VERIFY_SM2,
                ASN1_R_UNKNOWN_MESSAGE_DIGEST_ALGORITHM);
        goto err;
    }

    if (pkey == NULL) {
        X509err(X509_F_X509_VERIFY_SM2, ERR_R_PASSED_NULL_PARAMETER);
        return -1;
    }

    if (x->signature.type == V_ASN1_BIT_STRING && x->signature.flags & 0x7) {
        X509err(X509_F_X509_VERIFY_SM2, ASN1_R_INVALID_BIT_STRING_BITS_LEFT);
        return -1;
    }

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL) {
        X509err(X509_F_X509_VERIFY_SM2, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* Check public key OID matches public key type */
    if (EVP_PKEY_type(pknid) != pkey->ameth->pkey_id) {
        X509err(X509_F_X509_VERIFY_SM2, ASN1_R_WRONG_PUBLIC_KEY_TYPE);
        goto err;
    }

    if (!EVP_PKEY_set_alias_type(pkey, EVP_PKEY_SM2)) {
        X509err(X509_F_X509_VERIFY_SM2, ERR_R_EVP_LIB);
        ret = 0;
        goto err;
    }
    pctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (pctx == NULL) {
        X509err(X509_F_X509_VERIFY_SM2, ERR_R_EVP_LIB);
        ret = 0;
        goto err;
    }
    /* NOTE: we tolerate no actual ID, to provide maximum flexibility */
    if (x->sm2_id != NULL
            && EVP_PKEY_CTX_set1_id(pctx, x->sm2_id->data,
                                    x->sm2_id->length) != 1) {
        X509err(X509_F_X509_VERIFY_SM2, ERR_R_EVP_LIB);
        ret = 0;
        goto err;
    }
    EVP_MD_CTX_set_pkey_ctx(ctx, pctx);

    if (!EVP_DigestVerifyInit(ctx, NULL, type, NULL, pkey)) {
        X509err(X509_F_X509_VERIFY_SM2, ERR_R_EVP_LIB);
        ret = 0;
        goto err;
    }

    inl = ASN1_item_i2d((ASN1_VALUE *)&x->cert_info, &buf_in,
                        ASN1_ITEM_rptr(X509_CINF));
    if (inl <= 0) {
        X509err(X509_F_X509_VERIFY_SM2, ERR_R_INTERNAL_ERROR);
        goto err;
    }
    if (buf_in == NULL) {
        X509err(X509_F_X509_VERIFY_SM2, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    inll = inl;

    ret = EVP_DigestVerify(ctx, x->signature.data,
                           (size_t)x->signature.length, buf_in, inl);
    if (ret <= 0) {
        X509err(X509_F_X509_VERIFY_SM2, ERR_R_EVP_LIB);
        goto err;
    }
    ret = 1;
 err:
    OPENSSL_clear_free(buf_in, inll);
    EVP_MD_CTX_free(ctx);
    EVP_PKEY_CTX_free(pctx);
    return ret;
}