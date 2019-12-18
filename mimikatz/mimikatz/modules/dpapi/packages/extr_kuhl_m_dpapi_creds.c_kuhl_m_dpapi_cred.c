#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_2__ {int /*<<< orphan*/  blobSize; scalar_t__ blob; } ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  PKULL_M_CRED_LEGACY_CREDS_BLOB ;
typedef  int /*<<< orphan*/  PKULL_M_CRED_BLOB ;
typedef  TYPE_1__* PKUHL_M_DPAPI_ENCRYPTED_CRED ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  KULL_M_DPAPI_GUID_PROVIDER ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 scalar_t__ RtlEqualGuid (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ kuhl_m_dpapi_unprotect_raw_or_blob (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kull_m_cred_create (scalar_t__) ; 
 int /*<<< orphan*/  kull_m_cred_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_cred_descr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_cred_legacy_creds_create (scalar_t__) ; 
 int /*<<< orphan*/  kull_m_cred_legacy_creds_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_cred_legacy_creds_descr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_quick_descr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kull_m_file_readData (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_dpapi_cred(int argc, wchar_t * argv[])
{
	PCWSTR infile;
	PVOID file, out;
	DWORD szFile, szOut;
	BOOL isNT5Cred;
	PKULL_M_CRED_BLOB cred;
	PKULL_M_CRED_LEGACY_CREDS_BLOB legacyCreds;

	if(kull_m_string_args_byName(argc, argv, L"in", &infile, NULL))
	{
		if(kull_m_file_readData(infile, (PBYTE *) &file, &szFile))
		{
			isNT5Cred = RtlEqualGuid((PBYTE) file + sizeof(DWORD), &KULL_M_DPAPI_GUID_PROVIDER);
			kull_m_dpapi_blob_quick_descr(0, isNT5Cred ? file : ((PKUHL_M_DPAPI_ENCRYPTED_CRED) file)->blob);
			if(kuhl_m_dpapi_unprotect_raw_or_blob(isNT5Cred ? file : ((PKUHL_M_DPAPI_ENCRYPTED_CRED) file)->blob, isNT5Cred ? szFile : ((PKUHL_M_DPAPI_ENCRYPTED_CRED) file)->blobSize, NULL, argc, argv, NULL, 0, &out, &szOut, isNT5Cred ? L"Decrypting Legacy Credential(s):\n" : L"Decrypting Credential:\n"))
			{
				if(isNT5Cred)
				{
					if(legacyCreds = kull_m_cred_legacy_creds_create(out))
					{
						kull_m_cred_legacy_creds_descr(0, legacyCreds);
						kull_m_cred_legacy_creds_delete(legacyCreds);
					}
				}
				else 
				{
					if(cred = kull_m_cred_create(out))
					{
						kull_m_cred_descr(0, cred);
						kull_m_cred_delete(cred);
					}
				}
				LocalFree(out);
			}
			LocalFree(file);
		}
		else PRINT_ERROR_AUTO(L"kull_m_file_readData");
	}
	else PRINT_ERROR(L"Input CRED file needed (/in:file)\n");
	return STATUS_SUCCESS;
}