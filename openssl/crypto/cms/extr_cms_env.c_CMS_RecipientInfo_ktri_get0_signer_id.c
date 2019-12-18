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
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_7__ {int /*<<< orphan*/  rid; } ;
struct TYPE_5__ {TYPE_3__* ktri; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ d; } ;
typedef  TYPE_2__ CMS_RecipientInfo ;
typedef  TYPE_3__ CMS_KeyTransRecipientInfo ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_KTRI_GET0_SIGNER_ID ; 
 scalar_t__ CMS_RECIPINFO_TRANS ; 
 int /*<<< orphan*/  CMS_R_NOT_KEY_TRANSPORT ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cms_SignerIdentifier_get0_signer_id (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

int CMS_RecipientInfo_ktri_get0_signer_id(CMS_RecipientInfo *ri,
                                          ASN1_OCTET_STRING **keyid,
                                          X509_NAME **issuer,
                                          ASN1_INTEGER **sno)
{
    CMS_KeyTransRecipientInfo *ktri;
    if (ri->type != CMS_RECIPINFO_TRANS) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KTRI_GET0_SIGNER_ID,
               CMS_R_NOT_KEY_TRANSPORT);
        return 0;
    }
    ktri = ri->d.ktri;

    return cms_SignerIdentifier_get0_signer_id(ktri->rid, keyid, issuer, sno);
}