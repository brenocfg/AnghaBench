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

/* Variables and functions */
 scalar_t__ ERR_load_ASN1_strings () ; 
 scalar_t__ ERR_load_ASYNC_strings () ; 
 scalar_t__ ERR_load_BIO_strings () ; 
 scalar_t__ ERR_load_BN_strings () ; 
 scalar_t__ ERR_load_BUF_strings () ; 
 scalar_t__ ERR_load_CMP_strings () ; 
 scalar_t__ ERR_load_CMS_strings () ; 
 scalar_t__ ERR_load_COMP_strings () ; 
 scalar_t__ ERR_load_CONF_strings () ; 
 scalar_t__ ERR_load_CRMF_strings () ; 
 scalar_t__ ERR_load_CRYPTO_strings () ; 
 scalar_t__ ERR_load_CT_strings () ; 
 scalar_t__ ERR_load_DH_strings () ; 
 scalar_t__ ERR_load_DSA_strings () ; 
 scalar_t__ ERR_load_DSO_strings () ; 
 scalar_t__ ERR_load_EC_strings () ; 
 scalar_t__ ERR_load_ENGINE_strings () ; 
 scalar_t__ ERR_load_ERR_strings () ; 
 scalar_t__ ERR_load_ESS_strings () ; 
 scalar_t__ ERR_load_EVP_strings () ; 
 scalar_t__ ERR_load_OBJ_strings () ; 
 scalar_t__ ERR_load_OCSP_strings () ; 
 scalar_t__ ERR_load_OSSL_STORE_strings () ; 
 scalar_t__ ERR_load_PEM_strings () ; 
 scalar_t__ ERR_load_PKCS12_strings () ; 
 scalar_t__ ERR_load_PKCS7_strings () ; 
 scalar_t__ ERR_load_PROP_strings () ; 
 scalar_t__ ERR_load_PROV_strings () ; 
 scalar_t__ ERR_load_RAND_strings () ; 
 scalar_t__ ERR_load_RSA_strings () ; 
 scalar_t__ ERR_load_TS_strings () ; 
 scalar_t__ ERR_load_UI_strings () ; 
 scalar_t__ ERR_load_X509V3_strings () ; 
 scalar_t__ ERR_load_X509_strings () ; 

int err_load_crypto_strings_int(void)
{
    if (
#ifndef OPENSSL_NO_ERR
        ERR_load_ERR_strings() == 0 ||    /* include error strings for SYSerr */
        ERR_load_BN_strings() == 0 ||
# ifndef OPENSSL_NO_RSA
        ERR_load_RSA_strings() == 0 ||
# endif
# ifndef OPENSSL_NO_DH
        ERR_load_DH_strings() == 0 ||
# endif
        ERR_load_EVP_strings() == 0 ||
        ERR_load_BUF_strings() == 0 ||
        ERR_load_OBJ_strings() == 0 ||
        ERR_load_PEM_strings() == 0 ||
# ifndef OPENSSL_NO_DSA
        ERR_load_DSA_strings() == 0 ||
# endif
        ERR_load_X509_strings() == 0 ||
        ERR_load_ASN1_strings() == 0 ||
        ERR_load_CONF_strings() == 0 ||
        ERR_load_CRYPTO_strings() == 0 ||
# ifndef OPENSSL_NO_COMP
        ERR_load_COMP_strings() == 0 ||
# endif
# ifndef OPENSSL_NO_EC
        ERR_load_EC_strings() == 0 ||
# endif
        /* skip ERR_load_SSL_strings() because it is not in this library */
        ERR_load_BIO_strings() == 0 ||
        ERR_load_PKCS7_strings() == 0 ||
        ERR_load_X509V3_strings() == 0 ||
        ERR_load_PKCS12_strings() == 0 ||
        ERR_load_RAND_strings() == 0 ||
        ERR_load_DSO_strings() == 0 ||
# ifndef OPENSSL_NO_TS
        ERR_load_TS_strings() == 0 ||
# endif
# ifndef OPENSSL_NO_ENGINE
        ERR_load_ENGINE_strings() == 0 ||
# endif
# ifndef OPENSSL_NO_OCSP
        ERR_load_OCSP_strings() == 0 ||
# endif
        ERR_load_UI_strings() == 0 ||
# ifndef OPENSSL_NO_CMS
        ERR_load_CMS_strings() == 0 ||
# endif
# ifndef OPENSSL_NO_CRMF
        ERR_load_CRMF_strings() == 0 ||
        ERR_load_CMP_strings() == 0 ||
# endif
# ifndef OPENSSL_NO_CT
        ERR_load_CT_strings() == 0 ||
# endif
        ERR_load_ESS_strings() == 0 ||
        ERR_load_ASYNC_strings() == 0 ||
#endif
        ERR_load_OSSL_STORE_strings() == 0 ||
        ERR_load_PROP_strings() == 0 ||
        ERR_load_PROV_strings() == 0)
        return 0;

    return 1;
}