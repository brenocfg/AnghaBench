#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {size_t cbAttributes; TYPE_2__* pAttributes; int /*<<< orphan*/  pSid; } ;
struct TYPE_15__ {TYPE_4__* pAttr; } ;
struct TYPE_16__ {TYPE_5__ AttrBlock; } ;
struct TYPE_17__ {TYPE_6__ Entinf; } ;
struct TYPE_13__ {size_t valCount; size_t pAVal; } ;
struct TYPE_14__ {TYPE_3__ AttrVal; } ;
struct TYPE_12__ {TYPE_1__* pAttribute; } ;
struct TYPE_11__ {int /*<<< orphan*/  szAttributeName; int /*<<< orphan*/  fIsSensitive; } ;
typedef  TYPE_7__ REPLENTINFLIST ;
typedef  int /*<<< orphan*/  PSecPkgContext_SessionKey ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  TYPE_8__* PDCSHADOW_PUSH_REQUEST_OBJECT ;
typedef  size_t DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 size_t* GetSidSubAuthority (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__* GetSidSubAuthorityCount (int /*<<< orphan*/ *) ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcshadow_encode_sensitive_value (int,size_t,size_t,int /*<<< orphan*/ ) ; 

void kuhl_m_lsadump_dcshadow_encode_sensitive(REPLENTINFLIST *pReplEnt,  PDCSHADOW_PUSH_REQUEST_OBJECT object, PSecPkgContext_SessionKey SessionKey)
{
	DWORD i, j;
	BOOL fSupplRidEncryption = FALSE;
	DWORD dwRid = 0;
	PSID pSid = &(object->pSid);
	
	for(i = 0; i < object->cbAttributes; i++)
	{
		if(!object->pAttributes[i].pAttribute->fIsSensitive)
			continue;
		// special case for NTLM password reobfuscated with the RID of the account
		fSupplRidEncryption = (_wcsicmp(object->pAttributes[i].pAttribute->szAttributeName, L"unicodePwd")== 0 ||
					_wcsicmp(object->pAttributes[i].pAttribute->szAttributeName, L"dBCSPwd") == 0 ||
					_wcsicmp(object->pAttributes[i].pAttribute->szAttributeName, L"lmPwdHistory") == 0 ||
					_wcsicmp(object->pAttributes[i].pAttribute->szAttributeName, L"ntPwdHistory") == 0);
		if(fSupplRidEncryption)
			dwRid = *GetSidSubAuthority(pSid, (*GetSidSubAuthorityCount(pSid)) - 1);
		for(j = 0; j < pReplEnt->Entinf.AttrBlock.pAttr[i].AttrVal.valCount; j++)
			kuhl_m_lsadump_dcshadow_encode_sensitive_value(fSupplRidEncryption, dwRid, pReplEnt->Entinf.AttrBlock.pAttr[i].AttrVal.pAVal + j, SessionKey);
	}
}