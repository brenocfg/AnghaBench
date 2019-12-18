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
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ IXMLDOMNode_selectSingleNode (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  KULL_M_DPAPI_GUID_PROVIDER ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 scalar_t__ RtlEqualGuid (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  kprintf (char*,int,char*,int,int /*<<< orphan*/ *,...) ; 
 scalar_t__ kuhl_m_dpapi_unprotect_raw_or_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_quick_base64_to_Binary (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/ * kull_m_xml_getTextValue (int /*<<< orphan*/ *,char*) ; 

void kuhl_m_dpapi_rdg_LogonCredentials(DWORD level, IXMLDOMNode *pNode, int argc, wchar_t * argv[])
{
	IXMLDOMNode *pLogonCredentialsNode;
	wchar_t *userName, *domain, *password;
	LPBYTE data;
	LPVOID pDataOut;
	DWORD szData, dwDataOutLen;

	if((IXMLDOMNode_selectSingleNode(pNode, L"logonCredentials", &pLogonCredentialsNode) == S_OK) && pLogonCredentialsNode)
	{
		if(userName = kull_m_xml_getTextValue(pLogonCredentialsNode, L"userName"))
		{
			if(domain = kull_m_xml_getTextValue(pLogonCredentialsNode, L"domain"))
			{
				if(password = kull_m_xml_getTextValue(pLogonCredentialsNode, L"password"))
				{
					kprintf(L"%*s" L"* %s \\ %s : %s\n", level << 1, L"", domain, userName, password);
					if(kull_m_string_quick_base64_to_Binary(password, &data, &szData))
					{
						if(szData >= (sizeof(DWORD) + sizeof(GUID)))
						{
							if(RtlEqualGuid((PBYTE) data + sizeof(DWORD), &KULL_M_DPAPI_GUID_PROVIDER))
							{
								if(kuhl_m_dpapi_unprotect_raw_or_blob(data, szData, NULL, argc, argv, NULL, 0, &pDataOut, &dwDataOutLen, NULL))
								{
									kprintf(L"%*s" L">> cleartext password: %.*s\n", level << 1, L"", dwDataOutLen / sizeof(wchar_t), pDataOut);
									LocalFree(pDataOut);
								}
							}
							else PRINT_ERROR(L"Maybe certificate encryption (todo)\n");
						}
						else PRINT_ERROR(L"szData: %u\n", szData);
						LocalFree(data);
					}
					LocalFree(password);
				}
				LocalFree(domain);
			}
			LocalFree(userName);
		}
	}
}