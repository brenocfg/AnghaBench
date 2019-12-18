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
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_6__ {TYPE_1__* kari; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ d; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ukm; int /*<<< orphan*/ * keyEncryptionAlgorithm; } ;
typedef  TYPE_3__ CMS_RecipientInfo ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_KARI_GET0_ALG ; 
 scalar_t__ CMS_RECIPINFO_AGREE ; 
 int /*<<< orphan*/  CMS_R_NOT_KEY_AGREEMENT ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CMS_RecipientInfo_kari_get0_alg(CMS_RecipientInfo *ri,
                                    X509_ALGOR **palg,
                                    ASN1_OCTET_STRING **pukm)
{
    if (ri->type != CMS_RECIPINFO_AGREE) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KARI_GET0_ALG,
               CMS_R_NOT_KEY_AGREEMENT);
        return 0;
    }
    if (palg)
        *palg = ri->d.kari->keyEncryptionAlgorithm;
    if (pukm)
        *pukm = ri->d.kari->ukm;
    return 1;
}