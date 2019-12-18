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
typedef  int /*<<< orphan*/  PKCS7_SIGNER_INFO ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  NID_pkcs9_signingTime ; 
 int /*<<< orphan*/  PKCS7_F_DO_PKCS7_SIGNED_ATTRIB ; 
 int /*<<< orphan*/  PKCS7_SIGNER_INFO_sign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_add0_attrib_signing_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_add1_attrib_digest (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  PKCS7_get_signed_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_pkcs7_signed_attrib(PKCS7_SIGNER_INFO *si, EVP_MD_CTX *mctx)
{
    unsigned char md_data[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    /* Add signing time if not already present */
    if (!PKCS7_get_signed_attribute(si, NID_pkcs9_signingTime)) {
        if (!PKCS7_add0_attrib_signing_time(si, NULL)) {
            PKCS7err(PKCS7_F_DO_PKCS7_SIGNED_ATTRIB, ERR_R_MALLOC_FAILURE);
            return 0;
        }
    }

    /* Add digest */
    if (!EVP_DigestFinal_ex(mctx, md_data, &md_len)) {
        PKCS7err(PKCS7_F_DO_PKCS7_SIGNED_ATTRIB, ERR_R_EVP_LIB);
        return 0;
    }
    if (!PKCS7_add1_attrib_digest(si, md_data, md_len)) {
        PKCS7err(PKCS7_F_DO_PKCS7_SIGNED_ATTRIB, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    /* Now sign the attributes */
    if (!PKCS7_SIGNER_INFO_sign(si))
        return 0;

    return 1;
}