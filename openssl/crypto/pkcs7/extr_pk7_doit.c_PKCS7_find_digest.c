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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_TYPE_MD ; 
 int /*<<< orphan*/ * BIO_find_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_get_md_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int EVP_MD_CTX_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_FIND_DIGEST ; 
 int /*<<< orphan*/  PKCS7_R_UNABLE_TO_FIND_MESSAGE_DIGEST ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BIO *PKCS7_find_digest(EVP_MD_CTX **pmd, BIO *bio, int nid)
{
    for (;;) {
        bio = BIO_find_type(bio, BIO_TYPE_MD);
        if (bio == NULL) {
            PKCS7err(PKCS7_F_PKCS7_FIND_DIGEST,
                     PKCS7_R_UNABLE_TO_FIND_MESSAGE_DIGEST);
            return NULL;
        }
        BIO_get_md_ctx(bio, pmd);
        if (*pmd == NULL) {
            PKCS7err(PKCS7_F_PKCS7_FIND_DIGEST, ERR_R_INTERNAL_ERROR);
            return NULL;
        }
        if (EVP_MD_CTX_type(*pmd) == nid)
            return bio;
        bio = BIO_next(bio);
    }
    return NULL;
}