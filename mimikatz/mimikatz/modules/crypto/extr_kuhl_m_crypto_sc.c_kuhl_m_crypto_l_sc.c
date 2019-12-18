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
typedef  int /*<<< orphan*/  SCARDHANDLE ;
typedef  int /*<<< orphan*/  SCARDCONTEXT ;
typedef  scalar_t__* PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_SILENT ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LocalFree (scalar_t__*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  SCARD_ALL_READERS ; 
 int /*<<< orphan*/  SCARD_ATTR_ATR_STRING ; 
 int /*<<< orphan*/  SCARD_AUTOALLOCATE ; 
 int /*<<< orphan*/  SCARD_LEAVE_CARD ; 
 int SCARD_PROTOCOL_T0 ; 
 int SCARD_PROTOCOL_T1 ; 
 int /*<<< orphan*/  SCARD_PROVIDER_CARD_MODULE ; 
 int /*<<< orphan*/  SCARD_PROVIDER_CSP ; 
 int /*<<< orphan*/  SCARD_PROVIDER_KSP ; 
 int /*<<< orphan*/  SCARD_PROVIDER_PRIMARY ; 
 int /*<<< orphan*/  SCARD_SCOPE_SYSTEM ; 
 int /*<<< orphan*/  SCARD_SHARE_SHARED ; 
 scalar_t__ SCARD_S_SUCCESS ; 
 scalar_t__ SCARD_W_REMOVED_CARD ; 
 scalar_t__ SCardConnect (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCardDisconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SCardEstablishContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCardFreeMemory (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ SCardGetAttrib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ SCardGetCardTypeProviderName (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ SCardListCards (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ SCardListReaders (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCardReleaseContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_crypto_l_keys_capi (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_crypto_l_keys_cng (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_crypto_l_mdr (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__* kuhl_m_crypto_l_sc_containerFromReader (scalar_t__*) ; 
 int /*<<< orphan*/  kuhl_m_crypto_l_sc_prop (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  kuhl_m_crypto_l_sc_provtypefromname (scalar_t__*) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wcslen (scalar_t__*) ; 

NTSTATUS kuhl_m_crypto_l_sc(int argc, wchar_t * argv[])
{
	SCARDCONTEXT hContext;
	SCARDHANDLE hCard;
	PBYTE atr;
	LONG status;
	LPWSTR mszReaders = NULL, pReader, mszCards = NULL, pCard, szProvider = NULL, szContainer;
	DWORD dwLen = SCARD_AUTOALLOCATE, dwAtrLen;

	status = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
	if(status == SCARD_S_SUCCESS)
	{
		status = SCardListReaders(hContext, SCARD_ALL_READERS, (LPWSTR) &mszReaders, &dwLen);
		if(status == SCARD_S_SUCCESS)
		{
			kprintf(L"SmartCard readers:");
			for(pReader = mszReaders; *pReader; pReader += wcslen(pReader) + 1)
			{
				kprintf(L"\n * %s\n", pReader);
				kuhl_m_crypto_l_sc_prop(hContext, pReader);
				if(szContainer = kuhl_m_crypto_l_sc_containerFromReader(pReader))
				{
					status = SCardConnect(hContext, pReader, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwLen);
					if(status == SCARD_S_SUCCESS)
					{
						dwAtrLen = SCARD_AUTOALLOCATE;
						status = SCardGetAttrib(hCard, SCARD_ATTR_ATR_STRING, (PBYTE) &atr, &dwAtrLen);
						if(status == SCARD_S_SUCCESS)
						{
							kprintf(L"   ATR  : ");
							kull_m_string_wprintf_hex(atr, dwAtrLen, 0);
							kprintf(L"\n");
							dwLen = SCARD_AUTOALLOCATE;
							status = SCardListCards(hContext, atr, NULL, 0, (LPWSTR) &mszCards, &dwLen);
							if(status == SCARD_S_SUCCESS)
							{
								for(pCard = mszCards; pCard && *pCard; pCard += wcslen(pCard) + 1)
								{
									kprintf(L"   Model: %s\n", pCard);

									dwLen = SCARD_AUTOALLOCATE;
									status = SCardGetCardTypeProviderName(hContext, pCard, SCARD_PROVIDER_PRIMARY, (LPWSTR) &szProvider, &dwLen);
									if(status == SCARD_S_SUCCESS)
									{
										kprintf(L"   PRIM : %s\n", szProvider);
										SCardFreeMemory(hContext, szProvider);
									}
									else if(status != ERROR_FILE_NOT_FOUND) PRINT_ERROR(L"SCardGetCardTypeProviderName(PRIM): 0x%08x\n", status);

									dwLen = SCARD_AUTOALLOCATE;
									status = SCardGetCardTypeProviderName(hContext, pCard, SCARD_PROVIDER_CSP, (LPWSTR) &szProvider, &dwLen);
									if(status == SCARD_S_SUCCESS)
									{
										kprintf(L"   CSP  : %s\n", szProvider);
										if(dwLen = kuhl_m_crypto_l_sc_provtypefromname(szProvider))
											kuhl_m_crypto_l_keys_capi(szContainer, szProvider, dwLen, CRYPT_SILENT, FALSE, NULL);
										SCardFreeMemory(hContext, szProvider);
									}
									else if(status != ERROR_FILE_NOT_FOUND) PRINT_ERROR(L"SCardGetCardTypeProviderName(CSP): 0x%08x\n", status);

									dwLen = SCARD_AUTOALLOCATE;
									status = SCardGetCardTypeProviderName(hContext, pCard, SCARD_PROVIDER_KSP, (LPWSTR) &szProvider, &dwLen);
									if(status == SCARD_S_SUCCESS)
									{
										kprintf(L"   KSP  : %s\n", szProvider);
										kuhl_m_crypto_l_keys_cng(szContainer, szProvider, 0, FALSE, NULL);
										SCardFreeMemory(hContext, szProvider);
									}
									else if(status != ERROR_FILE_NOT_FOUND) PRINT_ERROR(L"SCardGetCardTypeProviderName(KSP): 0x%08x\n", status);

									dwLen = SCARD_AUTOALLOCATE;
									status = SCardGetCardTypeProviderName(hContext, pCard, SCARD_PROVIDER_CARD_MODULE, (LPWSTR) &szProvider, &dwLen);
									if(status == SCARD_S_SUCCESS)
									{
										kprintf(L"   MDRV : %s\n", szProvider);
										kuhl_m_crypto_l_mdr(szProvider, hContext, hCard, pCard, atr, dwAtrLen);
										SCardFreeMemory(hContext, szProvider);
									}
									else if(status != ERROR_FILE_NOT_FOUND) PRINT_ERROR(L"SCardGetCardTypeProviderName(MDR): 0x%08x\n", status);
								}
								SCardFreeMemory(hContext, mszCards);
							}
							else PRINT_ERROR(L"SCardListCards: 0x%08x\n", status);
							SCardFreeMemory(hContext, atr);
						}
						else PRINT_ERROR(L"SCardGetAttrib: 0x%08x (%u)\n", status, dwAtrLen);
						SCardDisconnect(hCard, SCARD_LEAVE_CARD);
					}
					else if(status != SCARD_W_REMOVED_CARD)
						PRINT_ERROR(L"SCardConnect: 0x%08x\n", status);
					LocalFree(szContainer);
				}
			}
			SCardFreeMemory(hContext, mszReaders);
		}
		else PRINT_ERROR(L"SCardListReaders: 0x%08x\n", status);
		SCardReleaseContext(hContext);
	}
	else PRINT_ERROR(L"SCardEstablishContext: 0x%08x\n", status);
	return STATUS_SUCCESS;
}