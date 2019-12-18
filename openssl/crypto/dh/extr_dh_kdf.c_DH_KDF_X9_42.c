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
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * EVP_KDF_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_free (int /*<<< orphan*/ *) ; 
 char* EVP_MD_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_MD_provider (int /*<<< orphan*/  const*) ; 
 int NID_undef ; 
 char* OBJ_nid2sn (int) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_X942KDF ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_CEK_ALG ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_UKM ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 void* OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 void* OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/ * ossl_provider_library_context (int /*<<< orphan*/  const*) ; 
 scalar_t__ strlen (char const*) ; 

int DH_KDF_X9_42(unsigned char *out, size_t outlen,
                 const unsigned char *Z, size_t Zlen,
                 ASN1_OBJECT *key_oid,
                 const unsigned char *ukm, size_t ukmlen, const EVP_MD *md)
{
    int ret = 0, nid;
    EVP_KDF_CTX *kctx = NULL;
    EVP_KDF *kdf = NULL;
    const char *oid_sn;
    OSSL_PARAM params[5], *p = params;
    const char *mdname = EVP_MD_name(md);
    const OSSL_PROVIDER *prov = EVP_MD_provider(md);
    OPENSSL_CTX *provctx = ossl_provider_library_context(prov);

    nid = OBJ_obj2nid(key_oid);
    if (nid == NID_undef)
        return 0;
    oid_sn = OBJ_nid2sn(nid);
    if (oid_sn == NULL)
        return 0;

    kdf = EVP_KDF_fetch(provctx, OSSL_KDF_NAME_X942KDF, NULL);
    if ((kctx = EVP_KDF_CTX_new(kdf)) == NULL)
        goto err;
    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST,
                                            (char *)mdname, strlen(mdname) + 1);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_KEY,
                                             (unsigned char *)Z, Zlen);
    if (ukm != NULL)
        *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_UKM,
                                                 (unsigned char *)ukm, ukmlen);
    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_CEK_ALG,
                                            (char *)oid_sn, strlen(oid_sn) + 1);
    *p = OSSL_PARAM_construct_end();
    ret = EVP_KDF_CTX_set_params(kctx, params) > 0
        && EVP_KDF_derive(kctx, out, outlen) > 0;
err:
    EVP_KDF_CTX_free(kctx);
    EVP_KDF_free(kdf);
    return ret;
}