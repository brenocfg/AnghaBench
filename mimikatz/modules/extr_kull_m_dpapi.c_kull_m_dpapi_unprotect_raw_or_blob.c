#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ pbData; scalar_t__ cbData; int /*<<< orphan*/  member_1; scalar_t__ member_0; } ;
struct TYPE_9__ {scalar_t__ dwDescriptionLen; scalar_t__ szDescription; } ;
typedef  TYPE_1__* PKULL_M_DPAPI_BLOB ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LPCVOID ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_2__ DATA_BLOB ;
typedef  int /*<<< orphan*/  CRYPTPROTECT_PROMPTSTRUCT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CryptUnprotectData (TYPE_2__*,scalar_t__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_1__* kull_m_dpapi_blob_create (scalar_t__) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  kull_m_dpapi_unprotect_blob (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

BOOL kull_m_dpapi_unprotect_raw_or_blob(LPCVOID pDataIn, DWORD dwDataInLen, LPWSTR *ppszDataDescr, LPCVOID pOptionalEntropy, DWORD dwOptionalEntropyLen, CRYPTPROTECT_PROMPTSTRUCT* pPromptStruct, DWORD dwFlags, LPVOID *pDataOut, DWORD *dwDataOutLen, LPCVOID pMasterKey, DWORD dwMasterKeyLen, LPCWSTR pPassword)
{
	BOOL status = FALSE;
	DATA_BLOB dataIn = {dwDataInLen, (PBYTE) pDataIn}, dataEntropy = {dwOptionalEntropyLen, (PBYTE) pOptionalEntropy}, dataOut;
	PKULL_M_DPAPI_BLOB blob;

	if(pMasterKey && dwMasterKeyLen)
	{
		if(blob = kull_m_dpapi_blob_create(pDataIn))
		{
			if(status = kull_m_dpapi_unprotect_blob(blob, pMasterKey, dwMasterKeyLen, pOptionalEntropy, dwOptionalEntropyLen, pPassword, pDataOut, dwDataOutLen))
				if(ppszDataDescr && blob->szDescription && blob->dwDescriptionLen)
					if(*ppszDataDescr = (LPWSTR) LocalAlloc(LPTR, blob->dwDescriptionLen))
						RtlCopyMemory(*ppszDataDescr, blob->szDescription, blob->dwDescriptionLen);
			kull_m_dpapi_blob_delete(blob);
		}
	}
	else
	{
		if(status = CryptUnprotectData(&dataIn, ppszDataDescr, &dataEntropy, NULL, pPromptStruct, dwFlags, &dataOut))
		{
			*dwDataOutLen = dataOut.cbData;
			if(*pDataOut = LocalAlloc(LPTR, *dwDataOutLen))
				RtlCopyMemory(*pDataOut, dataOut.pbData, *dwDataOutLen);
			LocalFree(dataOut.pbData);
		}
	}
	return status;
}