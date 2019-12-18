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
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LPCBYTE ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_iis_apphost_provider_decrypt (int,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_quick_base64_to_Binary (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_xml_getAttribute (int /*<<< orphan*/ *,char*) ; 

BOOL kuhl_m_iis_apphost_provider(int argc, wchar_t * argv[], IXMLDOMDocument *pXMLDom, IXMLDOMNode *pNode, LPCWSTR provider, LPCBYTE data, DWORD szData)
{
	BOOL status = FALSE, isMachine = FALSE;
	PWSTR name, type, keyContainerName, useMachineContainer, sessionKey;
	PBYTE binaryData;
	DWORD binaryDataLen;

	if(name = kull_m_xml_getAttribute(pNode, L"name"))
	{
		if(status = _wcsicmp(name, provider) == 0)
		{
			if(type = kull_m_xml_getAttribute(pNode, L"type"))
			{
				if(_wcsicmp(type, L"Microsoft.ApplicationHost.AesProtectedConfigurationProvider") == 0)
				{
					if(keyContainerName = kull_m_xml_getAttribute(pNode, L"keyContainerName"))
					{
						kprintf(L"  | KeyName   : %s\n", keyContainerName);
						if(sessionKey = kull_m_xml_getAttribute(pNode, L"sessionKey"))
						{
							//kprintf(L"SessionKey: %s\n", sessionKey);
							if(useMachineContainer = kull_m_xml_getAttribute(pNode, L"useMachineContainer"))
							{
								isMachine = (_wcsicmp(useMachineContainer, L"true") == 0);
								LocalFree(useMachineContainer);
							}		
							if(kull_m_string_quick_base64_to_Binary(sessionKey, &binaryData, &binaryDataLen))
							{
								kuhl_m_iis_apphost_provider_decrypt(argc, argv, keyContainerName, isMachine, binaryData, binaryDataLen, data, szData);
								LocalFree(binaryData);
							}
							LocalFree(sessionKey);
						}
						LocalFree(keyContainerName);
					}
				}
				else /*if ... */
				{
					PRINT_ERROR(L"type is not supported (%s)\n", type);
				}
				LocalFree(type);
			}
			else
			{
				// TODO direct decryption without session key
			}
		}
		LocalFree(name);
	}
	return status;
}