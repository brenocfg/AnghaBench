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
typedef  size_t PWCHAR ;
typedef  size_t PCWSTR ;
typedef  size_t PCWCHAR ;
typedef  size_t PBYTE ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IISXMLType_Providers ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  LocalFree (size_t) ; 
 int /*<<< orphan*/  RtlCopyMemory (size_t,size_t,size_t) ; 
 scalar_t__ _wcsnicmp (size_t,char*,int) ; 
 int /*<<< orphan*/  kprintf (char*,size_t,size_t) ; 
 int /*<<< orphan*/  kuhl_m_iis_apphost_genericEnumNodes (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_quick_base64_to_Binary (size_t,size_t*,int /*<<< orphan*/ *) ; 
 size_t wcschr (size_t,int) ; 
 size_t wcslen (size_t) ; 

void kuhl_m_iis_maybeEncrypted(int argc, wchar_t * argv[], IXMLDOMDocument *pXMLDom, PCWSTR password)
{
	BOOL status = FALSE;
	size_t passwordLen = wcslen(password), providerLen, dataLen;
	PCWCHAR pBeginProvider, pEndProvider, pBeginData, pEndData;
	PWCHAR provider, data;
	PBYTE binaryData;
	DWORD binaryDataLen;

	if(passwordLen > 10) // [enc:*:enc], and yes, I don't check all
	{
		if((_wcsnicmp(password, L"[enc:", 5) == 0) && (_wcsnicmp(password + (passwordLen - 5), L":enc]", 5) == 0))
		{
			pBeginProvider = password + 5;
			pEndProvider = wcschr(password + 5, L':');
			providerLen = (PBYTE) pEndProvider - (PBYTE) pBeginProvider;
			if(pEndProvider != (password + (passwordLen - 5)))
			{
				pBeginData = pEndProvider + 1;
				pEndData = password + (passwordLen - 5);
				dataLen = (PBYTE) pEndData - (PBYTE) pBeginData;
				if(provider = (PWCHAR) LocalAlloc(LPTR, providerLen + sizeof(wchar_t)))
				{
					RtlCopyMemory(provider, pBeginProvider, providerLen);
					if(data = (PWCHAR) LocalAlloc(LPTR, dataLen + sizeof(wchar_t)))
					{
						RtlCopyMemory(data, pBeginData, dataLen);
						kprintf(L"  | Provider  : %s\n  | Data      : %s\n", provider, data);

						if(kull_m_string_quick_base64_to_Binary(data, &binaryData, &binaryDataLen))
						{
							//kprintf(L"Binary    : ");
							//kull_m_string_wprintf_hex(binaryData, binaryDataLen, 0);
							//kprintf(L"\n");
							kuhl_m_iis_apphost_genericEnumNodes(argc, argv, pXMLDom, L"//configuration/configProtectedData/providers/add", IISXMLType_Providers, provider, binaryData, binaryDataLen);
							LocalFree(binaryData);
						}
						LocalFree(data);
					}
					LocalFree(provider);
				}
			}
		}
	}
}