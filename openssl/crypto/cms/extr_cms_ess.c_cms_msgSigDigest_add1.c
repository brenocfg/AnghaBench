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
typedef  int /*<<< orphan*/  CMS_SignerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_MSGSIGDIGEST_ADD1 ; 
 int /*<<< orphan*/  CMS_R_MSGSIGDIGEST_ERROR ; 
 int /*<<< orphan*/  CMS_signed_add1_attr_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  NID_id_smime_aa_msgSigDigest ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/  cms_msgSigDigest (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 

int cms_msgSigDigest_add1(CMS_SignerInfo *dest, CMS_SignerInfo *src)
{
    unsigned char dig[EVP_MAX_MD_SIZE];
    unsigned int diglen;
    if (!cms_msgSigDigest(src, dig, &diglen)) {
        CMSerr(CMS_F_CMS_MSGSIGDIGEST_ADD1, CMS_R_MSGSIGDIGEST_ERROR);
        return 0;
    }
    if (!CMS_signed_add1_attr_by_NID(dest, NID_id_smime_aa_msgSigDigest,
                                     V_ASN1_OCTET_STRING, dig, diglen)) {
        CMSerr(CMS_F_CMS_MSGSIGDIGEST_ADD1, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    return 1;
}