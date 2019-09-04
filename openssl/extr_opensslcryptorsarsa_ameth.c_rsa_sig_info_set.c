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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  X509_SIG_INFO ;
struct TYPE_4__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
typedef  int /*<<< orphan*/  RSA_PSS_PARAMS ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int EVP_MD_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_RSA_PSS ; 
 int NID_sha256 ; 
 int NID_sha384 ; 
 int NID_sha512 ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_PSS_PARAMS_free (int /*<<< orphan*/ *) ; 
 scalar_t__ X509_SIG_INFO_TLS ; 
 int /*<<< orphan*/  X509_SIG_INFO_set (int /*<<< orphan*/ *,int,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/ * rsa_pss_decode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  rsa_pss_get_param (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int*) ; 

__attribute__((used)) static int rsa_sig_info_set(X509_SIG_INFO *siginf, const X509_ALGOR *sigalg,
                            const ASN1_STRING *sig)
{
    int rv = 0;
    int mdnid, saltlen;
    uint32_t flags;
    const EVP_MD *mgf1md = NULL, *md = NULL;
    RSA_PSS_PARAMS *pss;

    /* Sanity check: make sure it is PSS */
    if (OBJ_obj2nid(sigalg->algorithm) != EVP_PKEY_RSA_PSS)
        return 0;
    /* Decode PSS parameters */
    pss = rsa_pss_decode(sigalg);
    if (!rsa_pss_get_param(pss, &md, &mgf1md, &saltlen))
        goto err;
    mdnid = EVP_MD_type(md);
    /*
     * For TLS need SHA256, SHA384 or SHA512, digest and MGF1 digest must
     * match and salt length must equal digest size
     */
    if ((mdnid == NID_sha256 || mdnid == NID_sha384 || mdnid == NID_sha512)
            && mdnid == EVP_MD_type(mgf1md) && saltlen == EVP_MD_size(md))
        flags = X509_SIG_INFO_TLS;
    else
        flags = 0;
    /* Note: security bits half number of digest bits */
    X509_SIG_INFO_set(siginf, mdnid, EVP_PKEY_RSA_PSS, EVP_MD_size(md) * 4,
                      flags);
    rv = 1;
    err:
    RSA_PSS_PARAMS_free(pss);
    return rv;
}