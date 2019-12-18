#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int /*<<< orphan*/  Buffer; int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kuhl_m_lsadump_LsaRetrievePrivateData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

NTSTATUS kuhl_m_lsadump_rpdata(int argc, wchar_t * argv[])
{
	NTSTATUS status;
	UNICODE_STRING secret;
	LPCWSTR szName, szSystem = NULL;
	BOOL export = kull_m_string_args_byName(argc, argv, L"export", NULL, NULL); // todo
	BOOL isSecret = kull_m_string_args_byName(argc, argv, L"secret", NULL, NULL);
	if(kull_m_string_args_byName(argc, argv, L"name", &szName, NULL))
	{
		kull_m_string_args_byName(argc, argv, L"system", &szSystem, NULL);
		status = kuhl_m_lsadump_LsaRetrievePrivateData(szSystem, szName, &secret, isSecret);
		if(NT_SUCCESS(status))
		{
			kull_m_string_wprintf_hex(secret.Buffer, secret.Length, 1 | (16<<16));
			LocalFree(secret.Buffer);
		}
		else PRINT_ERROR(L"kuhl_m_lsadump_LsaRetrievePrivateData: 0x%08x\n", status);
	}
	return STATUS_SUCCESS;
}