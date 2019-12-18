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
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_3__ {int /*<<< orphan*/  sid; } ;
typedef  TYPE_1__ CMS_SignerInfo ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int cms_SignerIdentifier_get0_signer_id (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

int CMS_SignerInfo_get0_signer_id(CMS_SignerInfo *si,
                                  ASN1_OCTET_STRING **keyid,
                                  X509_NAME **issuer, ASN1_INTEGER **sno)
{
    return cms_SignerIdentifier_get0_signer_id(si->sid, keyid, issuer, sno);
}