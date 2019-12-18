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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int ASN1_OCTET_STRING_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * X509_get0_subject_key_id (int /*<<< orphan*/ *) ; 

int cms_keyid_cert_cmp(ASN1_OCTET_STRING *keyid, X509 *cert)
{
    const ASN1_OCTET_STRING *cert_keyid = X509_get0_subject_key_id(cert);

    if (cert_keyid == NULL)
        return -1;
    return ASN1_OCTET_STRING_cmp(keyid, cert_keyid);
}