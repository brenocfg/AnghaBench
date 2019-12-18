#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_8__ {int member_0; int /*<<< orphan*/  dwPromptFlags; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_7__ {int cbData; scalar_t__ pbData; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  PKULL_M_DPAPI_BLOB ;
typedef  char* PCWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int DWORD ;
typedef  TYPE_1__ DATA_BLOB ;
typedef  TYPE_2__ CRYPTPROTECT_PROMPTSTRUCT ;

/* Variables and functions */
 int CRYPTPROTECT_LOCAL_MACHINE ; 
 int /*<<< orphan*/  CRYPTPROTECT_PROMPT_ON_PROTECT ; 
 int CRYPTPROTECT_SYSTEM ; 
 scalar_t__ CryptProtectData (TYPE_1__*,char*,TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/ * MIMIKATZ ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_create (scalar_t__) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_descr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_dpapi_displayPromptFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_dpapi_displayProtectionFlags (int) ; 
 scalar_t__ kull_m_file_writeData (char*,scalar_t__,int) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_stringToHexBuffer (char*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (scalar_t__,int,int) ; 
 int wcslen (char*) ; 

NTSTATUS kuhl_m_dpapi_protect(int argc, wchar_t * argv[]) // no support for protecting with RAW masterkey at this time
{
	DATA_BLOB dataIn, dataOut, dataEntropy = {0, NULL};
	PKULL_M_DPAPI_BLOB blob;
	PCWSTR description = NULL, szEntropy, outfile;
	CRYPTPROTECT_PROMPTSTRUCT promptStructure = {sizeof(CRYPTPROTECT_PROMPTSTRUCT), CRYPTPROTECT_PROMPT_ON_PROTECT, NULL, MIMIKATZ}, *pPrompt;
	DWORD flags = 0, outputMode = 1;

	kull_m_string_args_byName(argc, argv, L"data", (PCWSTR *) &dataIn.pbData, MIMIKATZ);
	kull_m_string_args_byName(argc, argv, L"description", &description, NULL);
	if(kull_m_string_args_byName(argc, argv, L"entropy", &szEntropy, NULL))
		kull_m_string_stringToHexBuffer(szEntropy, &dataEntropy.pbData, &dataEntropy.cbData);
	if(kull_m_string_args_byName(argc, argv, L"machine", NULL, NULL))
		flags |= CRYPTPROTECT_LOCAL_MACHINE;
	if(kull_m_string_args_byName(argc, argv, L"system", NULL, NULL))
		flags |= CRYPTPROTECT_SYSTEM;
	pPrompt = kull_m_string_args_byName(argc, argv, L"prompt", NULL, NULL) ? &promptStructure : NULL;
	
	if(kull_m_string_args_byName(argc, argv, L"c", NULL, NULL))
		outputMode = 2;

	kprintf(L"\ndata        : %s\n", dataIn.pbData);
	kprintf(L"description : %s\n", description ? description : L"");
	kprintf(L"flags       : "); kull_m_dpapi_displayProtectionFlags(flags); kprintf(L"\n");
	kprintf(L"prompt flags: "); if(pPrompt) kull_m_dpapi_displayPromptFlags(pPrompt->dwPromptFlags); kprintf(L"\n");
	kprintf(L"entropy     : "); kull_m_string_wprintf_hex(dataEntropy.pbData, dataEntropy.cbData, 0); kprintf(L"\n\n");

	dataIn.cbData = (DWORD) ((wcslen((PCWSTR) dataIn.pbData) + 1) * sizeof(wchar_t));
	if(CryptProtectData(&dataIn, description, &dataEntropy, NULL, pPrompt, flags, &dataOut))
	{
		if(blob = kull_m_dpapi_blob_create(dataOut.pbData))
		{
			kull_m_dpapi_blob_descr(0, blob);
			kull_m_dpapi_blob_delete(blob);
		}
		kprintf(L"\n");
		if(kull_m_string_args_byName(argc, argv, L"out", &outfile, NULL))
		{
			if(kull_m_file_writeData(outfile, dataOut.pbData, dataOut.cbData))
				kprintf(L"Write to file \'%s\' is OK\n", outfile);
		}
		else
		{
			kprintf(L"Blob:\n");
			kull_m_string_wprintf_hex(dataOut.pbData, dataOut.cbData, outputMode | (16 << 16));
			kprintf(L"\n");
		}
		LocalFree(dataOut.pbData);
	}
	else PRINT_ERROR_AUTO(L"CryptProtectData");

	if(dataEntropy.pbData)
		LocalFree(dataEntropy.pbData);

	return STATUS_SUCCESS;
}