#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* kari; TYPE_1__* ktri; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_3__ d; } ;
struct TYPE_15__ {TYPE_4__* ameth; } ;
struct TYPE_14__ {int (* pkey_ctrl ) (TYPE_5__*,int /*<<< orphan*/ ,int,TYPE_6__*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/ * pctx; } ;
struct TYPE_11__ {TYPE_5__* pkey; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  TYPE_5__ EVP_PKEY ;
typedef  TYPE_6__ CMS_RecipientInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_PKEY_CTRL_CMS_ENVELOPE ; 
 int /*<<< orphan*/  CMS_F_CMS_ENV_ASN1_CTRL ; 
 scalar_t__ CMS_RECIPINFO_AGREE ; 
 scalar_t__ CMS_RECIPINFO_TRANS ; 
 int /*<<< orphan*/  CMS_R_CTRL_FAILURE ; 
 int /*<<< orphan*/  CMS_R_NOT_SUPPORTED_FOR_THIS_KEY_TYPE ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* EVP_PKEY_CTX_get0_pkey (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_5__*,int /*<<< orphan*/ ,int,TYPE_6__*) ; 

int cms_env_asn1_ctrl(CMS_RecipientInfo *ri, int cmd)
{
    EVP_PKEY *pkey;
    int i;
    if (ri->type == CMS_RECIPINFO_TRANS)
        pkey = ri->d.ktri->pkey;
    else if (ri->type == CMS_RECIPINFO_AGREE) {
        EVP_PKEY_CTX *pctx = ri->d.kari->pctx;

        if (pctx == NULL)
            return 0;
        pkey = EVP_PKEY_CTX_get0_pkey(pctx);
        if (pkey == NULL)
            return 0;
    } else
        return 0;
    if (pkey->ameth == NULL || pkey->ameth->pkey_ctrl == NULL)
        return 1;
    i = pkey->ameth->pkey_ctrl(pkey, ASN1_PKEY_CTRL_CMS_ENVELOPE, cmd, ri);
    if (i == -2) {
        CMSerr(CMS_F_CMS_ENV_ASN1_CTRL,
               CMS_R_NOT_SUPPORTED_FOR_THIS_KEY_TYPE);
        return 0;
    }
    if (i <= 0) {
        CMSerr(CMS_F_CMS_ENV_ASN1_CTRL, CMS_R_CTRL_FAILURE);
        return 0;
    }
    return 1;
}