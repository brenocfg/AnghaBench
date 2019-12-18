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
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  SCARD_SCOPE_SYSTEM ; 
 scalar_t__ SCARD_S_SUCCESS ; 
 scalar_t__ SCardEstablishContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  kuhl_m_acr_Comm ; 
 int /*<<< orphan*/  kuhl_m_acr_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_acr_hContext ; 
 int /*<<< orphan*/  kuhl_m_acr_pn532Comm ; 
 scalar_t__ kull_m_acr_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_arcr_SendRecvDirect ; 
 int /*<<< orphan*/  kull_m_pn532_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_acr_open(int argc, wchar_t * argv[])
{
	LONG scStatus;
	BOOL isTrace = kull_m_string_args_byName(argc, argv, L"trace", NULL, NULL);

	if(!kuhl_m_acr_hContext)
	{
		scStatus = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &kuhl_m_acr_hContext);
		if(scStatus == SCARD_S_SUCCESS)
		{
			kprintf(L"Opening ACR  : ");
			if(kull_m_acr_init(kuhl_m_acr_hContext, L"ACS ACR122 0", TRUE, NULL, isTrace, &kuhl_m_acr_Comm))
			{
				kprintf(L"OK!\nOpening PN532: ");
				kull_m_pn532_init(kull_m_arcr_SendRecvDirect, &kuhl_m_acr_Comm, isTrace, &kuhl_m_acr_pn532Comm);
				kprintf(L"OK!\n");
			}
			else kuhl_m_acr_close(0, NULL);
		}
	}
	else PRINT_ERROR(L"Already opened, close it first\n");
	return STATUS_SUCCESS;
}