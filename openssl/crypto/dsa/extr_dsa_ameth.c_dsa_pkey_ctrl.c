#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
#define  ASN1_PKEY_CTRL_CMS_RI_TYPE 131 
#define  ASN1_PKEY_CTRL_CMS_SIGN 130 
#define  ASN1_PKEY_CTRL_DEFAULT_MD_NID 129 
#define  ASN1_PKEY_CTRL_PKCS7_SIGN 128 
 int CMS_RECIPINFO_NONE ; 
 int /*<<< orphan*/  CMS_SignerInfo_get0_algs (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**,TYPE_1__**) ; 
 int /*<<< orphan*/  EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int NID_sha256 ; 
 int NID_undef ; 
 int /*<<< orphan*/  OBJ_find_sigid_by_algs (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_SIGNER_INFO_get0_algs (void*,int /*<<< orphan*/ *,TYPE_1__**,TYPE_1__**) ; 
 int /*<<< orphan*/  V_ASN1_UNDEF ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_pkey_ctrl(EVP_PKEY *pkey, int op, long arg1, void *arg2)
{
    switch (op) {
    case ASN1_PKEY_CTRL_PKCS7_SIGN:
        if (arg1 == 0) {
            int snid, hnid;
            X509_ALGOR *alg1, *alg2;
            PKCS7_SIGNER_INFO_get0_algs(arg2, NULL, &alg1, &alg2);
            if (alg1 == NULL || alg1->algorithm == NULL)
                return -1;
            hnid = OBJ_obj2nid(alg1->algorithm);
            if (hnid == NID_undef)
                return -1;
            if (!OBJ_find_sigid_by_algs(&snid, hnid, EVP_PKEY_id(pkey)))
                return -1;
            X509_ALGOR_set0(alg2, OBJ_nid2obj(snid), V_ASN1_UNDEF, 0);
        }
        return 1;
#ifndef OPENSSL_NO_CMS
    case ASN1_PKEY_CTRL_CMS_SIGN:
        if (arg1 == 0) {
            int snid, hnid;
            X509_ALGOR *alg1, *alg2;
            CMS_SignerInfo_get0_algs(arg2, NULL, NULL, &alg1, &alg2);
            if (alg1 == NULL || alg1->algorithm == NULL)
                return -1;
            hnid = OBJ_obj2nid(alg1->algorithm);
            if (hnid == NID_undef)
                return -1;
            if (!OBJ_find_sigid_by_algs(&snid, hnid, EVP_PKEY_id(pkey)))
                return -1;
            X509_ALGOR_set0(alg2, OBJ_nid2obj(snid), V_ASN1_UNDEF, 0);
        }
        return 1;

    case ASN1_PKEY_CTRL_CMS_RI_TYPE:
        *(int *)arg2 = CMS_RECIPINFO_NONE;
        return 1;
#endif

    case ASN1_PKEY_CTRL_DEFAULT_MD_NID:
        *(int *)arg2 = NID_sha256;
        return 1;

    default:
        return -2;

    }

}