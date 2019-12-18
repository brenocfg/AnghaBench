#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_2__ X509_ALGOR ;
struct TYPE_12__ {TYPE_2__ signature; } ;
struct TYPE_14__ {int ex_flags; TYPE_1__ cert_info; scalar_t__ akid; } ;
typedef  TYPE_3__ X509 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_base_id (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_type (int) ; 
 int EXFLAG_PROXY ; 
 int /*<<< orphan*/  KU_DIGITAL_SIGNATURE ; 
 int /*<<< orphan*/  KU_KEY_CERT_SIGN ; 
 int NID_undef ; 
 int /*<<< orphan*/  OBJ_find_sigid_algs (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 scalar_t__ X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_V_ERR_KEYUSAGE_NO_CERTSIGN ; 
 int X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE ; 
 int X509_V_ERR_NO_ISSUER_PUBLIC_KEY ; 
 int X509_V_ERR_SIGNATURE_ALGORITHM_MISMATCH ; 
 int X509_V_ERR_SUBJECT_ISSUER_MISMATCH ; 
 int X509_V_OK ; 
 int X509_check_akid (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (TYPE_3__*) ; 
 int /*<<< orphan*/  X509_get_issuer_name (TYPE_3__*) ; 
 int /*<<< orphan*/  X509_get_subject_name (TYPE_3__*) ; 
 scalar_t__ ku_reject (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x509v3_cache_extensions (TYPE_3__*) ; 

int X509_check_issued(X509 *issuer, X509 *subject)
{
    if (X509_NAME_cmp(X509_get_subject_name(issuer),
                      X509_get_issuer_name(subject)))
        return X509_V_ERR_SUBJECT_ISSUER_MISMATCH;

    x509v3_cache_extensions(issuer);
    x509v3_cache_extensions(subject);

    if (subject->akid) {
        int ret = X509_check_akid(issuer, subject->akid);
        if (ret != X509_V_OK)
            return ret;
    }

    {
        /*
         * Check if the subject signature algorithm matches the issuer's PUBKEY
         * algorithm
         */
        EVP_PKEY *i_pkey = X509_get0_pubkey(issuer);
        X509_ALGOR *s_algor = &subject->cert_info.signature;
        int s_pknid = NID_undef, s_mdnid = NID_undef;

        if (i_pkey == NULL)
            return X509_V_ERR_NO_ISSUER_PUBLIC_KEY;

        if (!OBJ_find_sigid_algs(OBJ_obj2nid(s_algor->algorithm),
                                 &s_mdnid, &s_pknid)
            || EVP_PKEY_type(s_pknid) != EVP_PKEY_base_id(i_pkey))
            return X509_V_ERR_SIGNATURE_ALGORITHM_MISMATCH;
    }

    if (subject->ex_flags & EXFLAG_PROXY) {
        if (ku_reject(issuer, KU_DIGITAL_SIGNATURE))
            return X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE;
    } else if (ku_reject(issuer, KU_KEY_CERT_SIGN))
        return X509_V_ERR_KEYUSAGE_NO_CERTSIGN;
    return X509_V_OK;
}