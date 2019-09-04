#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {TYPE_1__* optionalSignature; } ;
struct TYPE_5__ {int /*<<< orphan*/ * certs; } ;
typedef  TYPE_1__ OCSP_SIGNATURE ;
typedef  TYPE_2__ OCSP_REQUEST ;

/* Variables and functions */
 TYPE_1__* OCSP_SIGNATURE_new () ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_X509_new_null () ; 
 int /*<<< orphan*/  sk_X509_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int OCSP_request_add1_cert(OCSP_REQUEST *req, X509 *cert)
{
    OCSP_SIGNATURE *sig;
    if (req->optionalSignature == NULL)
        req->optionalSignature = OCSP_SIGNATURE_new();
    sig = req->optionalSignature;
    if (sig == NULL)
        return 0;
    if (cert == NULL)
        return 1;
    if (sig->certs == NULL
        && (sig->certs = sk_X509_new_null()) == NULL)
        return 0;

    if (!sk_X509_push(sig->certs, cert))
        return 0;
    X509_up_ref(cert);
    return 1;
}