#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* sequence; } ;
struct TYPE_7__ {TYPE_2__ value; } ;
struct TYPE_5__ {unsigned char* data; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  PKCS7_SIGNER_INFO ;
typedef  int /*<<< orphan*/  ESS_SIGNING_CERT ;
typedef  TYPE_3__ ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  NID_id_smime_aa_signingCertificate ; 
 TYPE_3__* PKCS7_get_signed_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_ESS_SIGNING_CERT (int /*<<< orphan*/ *,unsigned char const**,int /*<<< orphan*/ ) ; 

ESS_SIGNING_CERT *ESS_SIGNING_CERT_get(PKCS7_SIGNER_INFO *si)
{
    ASN1_TYPE *attr;
    const unsigned char *p;
    attr = PKCS7_get_signed_attribute(si, NID_id_smime_aa_signingCertificate);
    if (!attr)
        return NULL;
    p = attr->value.sequence->data;
    return d2i_ESS_SIGNING_CERT(NULL, &p, attr->value.sequence->length);
}