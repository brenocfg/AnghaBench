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
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  OCSP_CERTID ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/ * OCSP_cert_id_new (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * X509_get0_pubkey_bitstr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * X509_get0_serialNumber (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * X509_get_issuer_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * X509_get_subject_name (int /*<<< orphan*/  const*) ; 

OCSP_CERTID *OCSP_cert_to_id(const EVP_MD *dgst, const X509 *subject,
                             const X509 *issuer)
{
    X509_NAME *iname;
    const ASN1_INTEGER *serial;
    ASN1_BIT_STRING *ikey;
    if (!dgst)
        dgst = EVP_sha1();
    if (subject) {
        iname = X509_get_issuer_name(subject);
        serial = X509_get0_serialNumber(subject);
    } else {
        iname = X509_get_subject_name(issuer);
        serial = NULL;
    }
    ikey = X509_get0_pubkey_bitstr(issuer);
    return OCSP_cert_id_new(dgst, iname, ikey, serial);
}