#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_11__ {TYPE_3__* other; int /*<<< orphan*/ * date; int /*<<< orphan*/ * keyIdentifier; } ;
struct TYPE_8__ {TYPE_1__* kekri; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_2__ d; } ;
struct TYPE_9__ {int /*<<< orphan*/ * keyAttr; int /*<<< orphan*/ * keyAttrId; } ;
struct TYPE_7__ {int /*<<< orphan*/ * keyEncryptionAlgorithm; TYPE_5__* kekid; } ;
typedef  TYPE_4__ CMS_RecipientInfo ;
typedef  TYPE_5__ CMS_KEKIdentifier ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_GENERALIZEDTIME ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_KEKRI_GET0_ID ; 
 scalar_t__ CMS_RECIPINFO_KEK ; 
 int /*<<< orphan*/  CMS_R_NOT_KEK ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CMS_RecipientInfo_kekri_get0_id(CMS_RecipientInfo *ri,
                                    X509_ALGOR **palg,
                                    ASN1_OCTET_STRING **pid,
                                    ASN1_GENERALIZEDTIME **pdate,
                                    ASN1_OBJECT **potherid,
                                    ASN1_TYPE **pothertype)
{
    CMS_KEKIdentifier *rkid;
    if (ri->type != CMS_RECIPINFO_KEK) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_GET0_ID, CMS_R_NOT_KEK);
        return 0;
    }
    rkid = ri->d.kekri->kekid;
    if (palg)
        *palg = ri->d.kekri->keyEncryptionAlgorithm;
    if (pid)
        *pid = rkid->keyIdentifier;
    if (pdate)
        *pdate = rkid->date;
    if (potherid) {
        if (rkid->other)
            *potherid = rkid->other->keyAttrId;
        else
            *potherid = NULL;
    }
    if (pothertype) {
        if (rkid->other)
            *pothertype = rkid->other->keyAttr;
        else
            *pothertype = NULL;
    }
    return 1;
}