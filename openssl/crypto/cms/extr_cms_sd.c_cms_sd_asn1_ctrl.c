#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* pkey; } ;
struct TYPE_8__ {TYPE_1__* ameth; } ;
struct TYPE_7__ {int (* pkey_ctrl ) (TYPE_2__*,int /*<<< orphan*/ ,int,TYPE_3__*) ;} ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  TYPE_3__ CMS_SignerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_PKEY_CTRL_CMS_SIGN ; 
 int /*<<< orphan*/  CMS_F_CMS_SD_ASN1_CTRL ; 
 int /*<<< orphan*/  CMS_R_CTRL_FAILURE ; 
 int /*<<< orphan*/  CMS_R_NOT_SUPPORTED_FOR_THIS_KEY_TYPE ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,TYPE_3__*) ; 

__attribute__((used)) static int cms_sd_asn1_ctrl(CMS_SignerInfo *si, int cmd)
{
    EVP_PKEY *pkey = si->pkey;
    int i;
    if (pkey->ameth == NULL || pkey->ameth->pkey_ctrl == NULL)
        return 1;
    i = pkey->ameth->pkey_ctrl(pkey, ASN1_PKEY_CTRL_CMS_SIGN, cmd, si);
    if (i == -2) {
        CMSerr(CMS_F_CMS_SD_ASN1_CTRL, CMS_R_NOT_SUPPORTED_FOR_THIS_KEY_TYPE);
        return 0;
    }
    if (i <= 0) {
        CMSerr(CMS_F_CMS_SD_ASN1_CTRL, CMS_R_CTRL_FAILURE);
        return 0;
    }
    return 1;
}