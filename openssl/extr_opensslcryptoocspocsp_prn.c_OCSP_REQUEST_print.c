#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  singleRequestExtensions; int /*<<< orphan*/ * reqCert; } ;
struct TYPE_9__ {int /*<<< orphan*/  requestExtensions; int /*<<< orphan*/  requestList; int /*<<< orphan*/ * requestorName; int /*<<< orphan*/  version; } ;
struct TYPE_8__ {TYPE_1__* optionalSignature; TYPE_3__ tbsRequest; } ;
struct TYPE_7__ {int /*<<< orphan*/  certs; int /*<<< orphan*/  signature; int /*<<< orphan*/  signatureAlgorithm; } ;
typedef  TYPE_1__ OCSP_SIGNATURE ;
typedef  TYPE_2__ OCSP_REQUEST ;
typedef  TYPE_3__ OCSP_REQINFO ;
typedef  TYPE_4__ OCSP_ONEREQ ;
typedef  int /*<<< orphan*/  OCSP_CERTID ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 long ASN1_INTEGER_get (int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,long,long) ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  GENERAL_NAME_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_write_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509V3_extensions_print (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  X509_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_signature_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocsp_certid_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sk_OCSP_ONEREQ_num (int /*<<< orphan*/ ) ; 
 TYPE_4__* sk_OCSP_ONEREQ_value (int /*<<< orphan*/ ,int) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_value (int /*<<< orphan*/ ,int) ; 

int OCSP_REQUEST_print(BIO *bp, OCSP_REQUEST *o, unsigned long flags)
{
    int i;
    long l;
    OCSP_CERTID *cid = NULL;
    OCSP_ONEREQ *one = NULL;
    OCSP_REQINFO *inf = &o->tbsRequest;
    OCSP_SIGNATURE *sig = o->optionalSignature;

    if (BIO_write(bp, "OCSP Request Data:\n", 19) <= 0)
        goto err;
    l = ASN1_INTEGER_get(inf->version);
    if (BIO_printf(bp, "    Version: %lu (0x%lx)", l + 1, l) <= 0)
        goto err;
    if (inf->requestorName != NULL) {
        if (BIO_write(bp, "\n    Requestor Name: ", 21) <= 0)
            goto err;
        GENERAL_NAME_print(bp, inf->requestorName);
    }
    if (BIO_write(bp, "\n    Requestor List:\n", 21) <= 0)
        goto err;
    for (i = 0; i < sk_OCSP_ONEREQ_num(inf->requestList); i++) {
        one = sk_OCSP_ONEREQ_value(inf->requestList, i);
        cid = one->reqCert;
        ocsp_certid_print(bp, cid, 8);
        if (!X509V3_extensions_print(bp,
                                     "Request Single Extensions",
                                     one->singleRequestExtensions, flags, 8))
            goto err;
    }
    if (!X509V3_extensions_print(bp, "Request Extensions",
                                 inf->requestExtensions, flags, 4))
        goto err;
    if (sig) {
        X509_signature_print(bp, &sig->signatureAlgorithm, sig->signature);
        for (i = 0; i < sk_X509_num(sig->certs); i++) {
            X509_print(bp, sk_X509_value(sig->certs, i));
            PEM_write_bio_X509(bp, sk_X509_value(sig->certs, i));
        }
    }
    return 1;
 err:
    return 0;
}