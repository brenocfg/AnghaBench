#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_13__ {TYPE_2__* ameth; } ;
struct TYPE_12__ {int /*<<< orphan*/  digest_alg; TYPE_4__* pkey; TYPE_1__* issuer_and_serial; int /*<<< orphan*/  version; } ;
struct TYPE_11__ {int (* pkey_ctrl ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  issuer; } ;
typedef  TYPE_3__ PKCS7_SIGNER_INFO ;
typedef  TYPE_4__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASN1_PKEY_CTRL_PKCS7_SIGN ; 
 int /*<<< orphan*/  EVP_MD_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_up_ref (TYPE_4__*) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_SIGNER_INFO_SET ; 
 int /*<<< orphan*/  PKCS7_R_SIGNING_CTRL_FAILURE ; 
 int /*<<< orphan*/  PKCS7_R_SIGNING_NOT_SUPPORTED_FOR_THIS_KEY_TYPE ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_NULL ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_serialNumber (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

int PKCS7_SIGNER_INFO_set(PKCS7_SIGNER_INFO *p7i, X509 *x509, EVP_PKEY *pkey,
                          const EVP_MD *dgst)
{
    int ret;

    /* We now need to add another PKCS7_SIGNER_INFO entry */
    if (!ASN1_INTEGER_set(p7i->version, 1))
        goto err;
    if (!X509_NAME_set(&p7i->issuer_and_serial->issuer,
                       X509_get_issuer_name(x509)))
        goto err;

    /*
     * because ASN1_INTEGER_set is used to set a 'long' we will do things the
     * ugly way.
     */
    ASN1_INTEGER_free(p7i->issuer_and_serial->serial);
    if (!(p7i->issuer_and_serial->serial =
          ASN1_INTEGER_dup(X509_get_serialNumber(x509))))
        goto err;

    /* lets keep the pkey around for a while */
    EVP_PKEY_up_ref(pkey);
    p7i->pkey = pkey;

    /* Set the algorithms */

    X509_ALGOR_set0(p7i->digest_alg, OBJ_nid2obj(EVP_MD_type(dgst)),
                    V_ASN1_NULL, NULL);

    if (pkey->ameth && pkey->ameth->pkey_ctrl) {
        ret = pkey->ameth->pkey_ctrl(pkey, ASN1_PKEY_CTRL_PKCS7_SIGN, 0, p7i);
        if (ret > 0)
            return 1;
        if (ret != -2) {
            PKCS7err(PKCS7_F_PKCS7_SIGNER_INFO_SET,
                     PKCS7_R_SIGNING_CTRL_FAILURE);
            return 0;
        }
    }
    PKCS7err(PKCS7_F_PKCS7_SIGNER_INFO_SET,
             PKCS7_R_SIGNING_NOT_SUPPORTED_FOR_THIS_KEY_TYPE);
 err:
    return 0;
}