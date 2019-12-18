#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_12__ {TYPE_2__* ameth; } ;
struct TYPE_11__ {int /*<<< orphan*/ * cert; TYPE_1__* issuer_and_serial; int /*<<< orphan*/  version; } ;
struct TYPE_10__ {int (* pkey_ctrl ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  issuer; } ;
typedef  TYPE_3__ PKCS7_RECIP_INFO ;
typedef  TYPE_4__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_PKEY_CTRL_PKCS7_ENCRYPT ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_RECIP_INFO_SET ; 
 int /*<<< orphan*/  PKCS7_R_ENCRYPTION_CTRL_FAILURE ; 
 int /*<<< orphan*/  PKCS7_R_ENCRYPTION_NOT_SUPPORTED_FOR_THIS_KEY_TYPE ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_serialNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

int PKCS7_RECIP_INFO_set(PKCS7_RECIP_INFO *p7i, X509 *x509)
{
    int ret;
    EVP_PKEY *pkey = NULL;
    if (!ASN1_INTEGER_set(p7i->version, 0))
        return 0;
    if (!X509_NAME_set(&p7i->issuer_and_serial->issuer,
                       X509_get_issuer_name(x509)))
        return 0;

    ASN1_INTEGER_free(p7i->issuer_and_serial->serial);
    if (!(p7i->issuer_and_serial->serial =
          ASN1_INTEGER_dup(X509_get_serialNumber(x509))))
        return 0;

    pkey = X509_get0_pubkey(x509);

    if (!pkey || !pkey->ameth || !pkey->ameth->pkey_ctrl) {
        PKCS7err(PKCS7_F_PKCS7_RECIP_INFO_SET,
                 PKCS7_R_ENCRYPTION_NOT_SUPPORTED_FOR_THIS_KEY_TYPE);
        goto err;
    }

    ret = pkey->ameth->pkey_ctrl(pkey, ASN1_PKEY_CTRL_PKCS7_ENCRYPT, 0, p7i);
    if (ret == -2) {
        PKCS7err(PKCS7_F_PKCS7_RECIP_INFO_SET,
                 PKCS7_R_ENCRYPTION_NOT_SUPPORTED_FOR_THIS_KEY_TYPE);
        goto err;
    }
    if (ret <= 0) {
        PKCS7err(PKCS7_F_PKCS7_RECIP_INFO_SET,
                 PKCS7_R_ENCRYPTION_CTRL_FAILURE);
        goto err;
    }

    X509_up_ref(x509);
    p7i->cert = x509;

    return 1;

 err:
    return 0;
}