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
typedef  int /*<<< orphan*/  PKULL_M_DPAPI_MASTERKEYS ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kull_m_dpapi_masterkeys_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_dpapi_masterkeys_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_dpapi_masterkeys_descr (int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_file_readData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_dpapi_masterkeys(int argc, wchar_t * argv[])
{
	PKULL_M_DPAPI_MASTERKEYS masterkeys;
	PBYTE buffer;
	DWORD szBuffer;

	if(argc && kull_m_file_readData(argv[0], &buffer, &szBuffer))
	{
		if(masterkeys = kull_m_dpapi_masterkeys_create(buffer))
		{
			kull_m_dpapi_masterkeys_descr(masterkeys);
			kull_m_dpapi_masterkeys_delete(masterkeys);
		}
		LocalFree(buffer);
	}
	return STATUS_SUCCESS;
}