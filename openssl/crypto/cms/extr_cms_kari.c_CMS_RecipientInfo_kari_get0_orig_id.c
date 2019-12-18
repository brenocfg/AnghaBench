#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_13__ {TYPE_4__* originatorKey; int /*<<< orphan*/ * subjectKeyIdentifier; TYPE_3__* issuerAndSerialNumber; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_5__ d; } ;
struct TYPE_10__ {TYPE_1__* kari; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_2__ d; } ;
struct TYPE_12__ {int /*<<< orphan*/ * publicKey; int /*<<< orphan*/ * algorithm; } ;
struct TYPE_11__ {int /*<<< orphan*/ * serialNumber; int /*<<< orphan*/ * issuer; } ;
struct TYPE_9__ {TYPE_7__* originator; } ;
typedef  TYPE_6__ CMS_RecipientInfo ;
typedef  TYPE_7__ CMS_OriginatorIdentifierOrKey ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_KARI_GET0_ORIG_ID ; 
 scalar_t__ CMS_OIK_ISSUER_SERIAL ; 
 scalar_t__ CMS_OIK_KEYIDENTIFIER ; 
 scalar_t__ CMS_OIK_PUBKEY ; 
 scalar_t__ CMS_RECIPINFO_AGREE ; 
 int /*<<< orphan*/  CMS_R_NOT_KEY_AGREEMENT ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CMS_RecipientInfo_kari_get0_orig_id(CMS_RecipientInfo *ri,
                                        X509_ALGOR **pubalg,
                                        ASN1_BIT_STRING **pubkey,
                                        ASN1_OCTET_STRING **keyid,
                                        X509_NAME **issuer,
                                        ASN1_INTEGER **sno)
{
    CMS_OriginatorIdentifierOrKey *oik;
    if (ri->type != CMS_RECIPINFO_AGREE) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KARI_GET0_ORIG_ID,
               CMS_R_NOT_KEY_AGREEMENT);
        return 0;
    }
    oik = ri->d.kari->originator;
    if (issuer)
        *issuer = NULL;
    if (sno)
        *sno = NULL;
    if (keyid)
        *keyid = NULL;
    if (pubalg)
        *pubalg = NULL;
    if (pubkey)
        *pubkey = NULL;
    if (oik->type == CMS_OIK_ISSUER_SERIAL) {
        if (issuer)
            *issuer = oik->d.issuerAndSerialNumber->issuer;
        if (sno)
            *sno = oik->d.issuerAndSerialNumber->serialNumber;
    } else if (oik->type == CMS_OIK_KEYIDENTIFIER) {
        if (keyid)
            *keyid = oik->d.subjectKeyIdentifier;
    } else if (oik->type == CMS_OIK_PUBKEY) {
        if (pubalg)
            *pubalg = oik->d.originatorKey->algorithm;
        if (pubkey)
            *pubkey = oik->d.originatorKey->publicKey;
    } else
        return 0;
    return 1;
}