#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_f_md () ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR_R_BIO_LIB ; 
 int /*<<< orphan*/ * EVP_get_digestbyobj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_BIO_ADD_DIGEST ; 
 int /*<<< orphan*/  PKCS7_R_UNKNOWN_DIGEST_TYPE ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int PKCS7_bio_add_digest(BIO **pbio, X509_ALGOR *alg)
{
    BIO *btmp;
    const EVP_MD *md;
    if ((btmp = BIO_new(BIO_f_md())) == NULL) {
        PKCS7err(PKCS7_F_PKCS7_BIO_ADD_DIGEST, ERR_R_BIO_LIB);
        goto err;
    }

    md = EVP_get_digestbyobj(alg->algorithm);
    if (md == NULL) {
        PKCS7err(PKCS7_F_PKCS7_BIO_ADD_DIGEST, PKCS7_R_UNKNOWN_DIGEST_TYPE);
        goto err;
    }

    BIO_set_md(btmp, md);
    if (*pbio == NULL)
        *pbio = btmp;
    else if (!BIO_push(*pbio, btmp)) {
        PKCS7err(PKCS7_F_PKCS7_BIO_ADD_DIGEST, ERR_R_BIO_LIB);
        goto err;
    }
    btmp = NULL;

    return 1;

 err:
    BIO_free(btmp);
    return 0;

}