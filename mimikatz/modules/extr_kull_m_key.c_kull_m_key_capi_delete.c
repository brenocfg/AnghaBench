#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* pExExportFlag; struct TYPE_4__* pExPrivateKey; struct TYPE_4__* pExPublicKey; struct TYPE_4__* pSiExportFlag; struct TYPE_4__* pSiPrivateKey; struct TYPE_4__* pSiPublicKey; struct TYPE_4__* pHash; struct TYPE_4__* pName; } ;
typedef  TYPE_1__* PKULL_M_KEY_CAPI_BLOB ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 

void kull_m_key_capi_delete(PKULL_M_KEY_CAPI_BLOB capiKey)
{
	if(capiKey)
	{
		if(capiKey->pName)
			LocalFree(capiKey->pName);
		if(capiKey->pHash)
			LocalFree(capiKey->pHash);
		if(capiKey->pSiPublicKey)
			LocalFree(capiKey->pSiPublicKey);
		if(capiKey->pSiPrivateKey)
			LocalFree(capiKey->pSiPrivateKey);
		if(capiKey->pSiExportFlag)
			LocalFree(capiKey->pSiExportFlag);
		if(capiKey->pExPublicKey)
			LocalFree(capiKey->pExPublicKey);
		if(capiKey->pExPrivateKey)
			LocalFree(capiKey->pExPrivateKey);
		if(capiKey->pExExportFlag)
			LocalFree(capiKey->pExExportFlag);
		LocalFree(capiKey);
	}
}