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
struct TYPE_2__ {int /*<<< orphan*/ * pbData; int /*<<< orphan*/  cbData; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/  PKULL_M_DPAPI_BLOB ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_1__ DATA_BLOB ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kuhl_m_dpapi_unprotect_raw_or_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_descr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_file_readData (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_file_writeData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_printSuspectUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_dpapi_blob(int argc, wchar_t * argv[])
{
	DATA_BLOB dataIn, dataOut;
	PKULL_M_DPAPI_BLOB blob;
	PCWSTR outfile, infile;
	PWSTR description = NULL;

	if(kull_m_string_args_byName(argc, argv, L"in", &infile, NULL))
	{
		if(kull_m_file_readData(infile, &dataIn.pbData, &dataIn.cbData))
		{
			if(blob = kull_m_dpapi_blob_create(dataIn.pbData))
			{
				kull_m_dpapi_blob_descr(0, blob);

				if(kuhl_m_dpapi_unprotect_raw_or_blob(dataIn.pbData, dataIn.cbData, &description, argc, argv, NULL, 0, (LPVOID *) &dataOut.pbData, &dataOut.cbData, NULL))
				{
					if(description)
					{
						kprintf(L"description : %s\n", description);
						LocalFree(description);
					}

					if(kull_m_string_args_byName(argc, argv, L"out", &outfile, NULL))
					{
						if(kull_m_file_writeData(outfile, dataOut.pbData, dataOut.cbData))
							kprintf(L"Write to file \'%s\' is OK\n", outfile);
					}
					else
					{
						kprintf(L"data: ");
						kull_m_string_printSuspectUnicodeString(dataOut.pbData, dataOut.cbData);
						kprintf(L"\n");
					}
					LocalFree(dataOut.pbData);
				}
				kull_m_dpapi_blob_delete(blob);
			}
			LocalFree(dataIn.pbData);
		}
		else PRINT_ERROR_AUTO(L"kull_m_file_readData");
	}
	return STATUS_SUCCESS;
}