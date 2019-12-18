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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IXMLDOMNode_get_nodeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _wcsicmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kprintf (char*,int,...) ; 
 scalar_t__ kuhl_m_dpapi_unprotect_raw_or_blob (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_quick_descr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_stringToHexBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

void kuhl_m_dpapi_powershell_try_SecureString(IXMLDOMNode *pObj, int argc, wchar_t * argv[])
{
	BOOL isSecureString = FALSE;
	BSTR bstrGeneric;
	LPBYTE data;
	LPVOID pDataOut;
	DWORD szData, dwDataOutLen;

	if(IXMLDOMNode_get_nodeName(pObj, &bstrGeneric) == S_OK)
	{
		isSecureString = !_wcsicmp(bstrGeneric, L"SS");
		SysFreeString(bstrGeneric);
		if(IXMLDOMNode_get_text(pObj, &bstrGeneric) == S_OK)
		{
			if(isSecureString)
			{
				if(kull_m_string_stringToHexBuffer(bstrGeneric, &data, &szData))
				{
					kull_m_dpapi_blob_quick_descr(0, data);
					if(kuhl_m_dpapi_unprotect_raw_or_blob(data, szData, NULL, argc, argv, NULL, 0, &pDataOut, &dwDataOutLen, NULL))
					{
						kprintf(L">> cleartext: %.*s\n", dwDataOutLen / sizeof(wchar_t), pDataOut);
						LocalFree(pDataOut);
					}
					LocalFree(data);
				}
			}
			else kprintf(L"%s\n", bstrGeneric);
			SysFreeString(bstrGeneric);
		}
	}
}