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
struct hierarchy_data {TYPE_2__* pCertViewInfo; } ;
struct TYPE_7__ {int csCertChain; } ;
struct TYPE_5__ {scalar_t__ pCryptProviderData; } ;
struct TYPE_6__ {int /*<<< orphan*/  idxCounterSigner; int /*<<< orphan*/  fCounterSigner; int /*<<< orphan*/  idxSigner; TYPE_1__ u; } ;
typedef  int LPARAM ;
typedef  int DWORD ;
typedef  TYPE_3__ CRYPT_PROVIDER_SGNR ;
typedef  int /*<<< orphan*/  CRYPT_PROVIDER_DATA ;

/* Variables and functions */
 TYPE_3__* WTHelperGetProvSignerFromChain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline DWORD lparam_to_index(struct hierarchy_data *data, LPARAM lp)
{
    CRYPT_PROVIDER_SGNR *provSigner = WTHelperGetProvSignerFromChain(
     (CRYPT_PROVIDER_DATA *)data->pCertViewInfo->u.pCryptProviderData,
     data->pCertViewInfo->idxSigner, data->pCertViewInfo->fCounterSigner,
     data->pCertViewInfo->idxCounterSigner);

    if (!(lp & 1))
        return provSigner->csCertChain - 1;
    return lp >> 1;
}