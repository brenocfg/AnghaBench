#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kuhl_m_dpapi_unprotect_raw_or_blob (scalar_t__,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_quick_descr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kull_m_file_readData (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_qad_ansi_to_unicode (char const*) ; 
 scalar_t__ kull_m_string_quickxml_simplefind (scalar_t__,char*,scalar_t__*) ; 
 scalar_t__ kull_m_string_stringToHexBuffer (scalar_t__,scalar_t__*,int*) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (scalar_t__,int,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_dpapi_wwan(int argc, wchar_t * argv[])
{
	PBYTE pFile, hex, dataOut;
	DWORD dwData, lenHex, lenDataOut;
	LPWSTR dataU, dataF;
	LPCWSTR infile;

	if(kull_m_string_args_byName(argc, argv, L"in", &infile, NULL))
	{
		if(kull_m_file_readData(infile, &pFile, &dwData))
		{
			if(dataU = kull_m_string_qad_ansi_to_unicode((const char *) pFile))
			{
				if(kull_m_string_quickxml_simplefind(dataU, L"Name", &dataF))
				{
					kprintf(L"Profile \'%s\'\n\n", dataF);
					LocalFree(dataF);
				}
				if(kull_m_string_quickxml_simplefind(dataU, L"AccessString", &dataF))
				{
					kprintf(L" * AccessString    : %s\n", dataF);
					LocalFree(dataF);
				}
				if(kull_m_string_quickxml_simplefind(dataU, L"SubscriberID", &dataF))
				{
					if(kull_m_string_stringToHexBuffer(dataF, &hex, &lenHex))
					{
						kprintf(L"\n");
						kull_m_dpapi_blob_quick_descr(0, hex);
						if(kuhl_m_dpapi_unprotect_raw_or_blob(hex, lenHex, NULL, argc, argv, NULL, 0, (LPVOID *) &dataOut, &lenDataOut, NULL))
						{
							kprintf(L" * SubscriberID  : ");
							kull_m_string_wprintf_hex(dataOut, lenDataOut, 0);
							kprintf(L"\n");
							kprintf(L"%.*s", lenDataOut / sizeof(wchar_t), dataOut);
							LocalFree(dataOut);
						}
						LocalFree(hex);
					}
					LocalFree(dataF);
				}
				LocalFree(dataU);
			}
			LocalFree(pFile);
		}
		else PRINT_ERROR_AUTO(L"kull_m_file_readData");
	}
	else PRINT_ERROR(L"Input Wwan XML profile needed (/in:file)\n");
	return STATUS_SUCCESS;
}