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
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IXMLDOMDocument_selectSingleNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ S_OK ; 
 scalar_t__ kuhl_m_dpapi_powershell_check_against_one_type (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_powershell_credential (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_powershell_try_SecureString (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kull_m_xml_CreateAndInitDOM () ; 
 scalar_t__ kull_m_xml_LoadXMLFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_xml_ReleaseDom (int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_dpapi_powershell(int argc, wchar_t * argv[])
{
	PCWSTR filename;
	IXMLDOMDocument *pXMLDom;
	IXMLDOMNode *pNode;

	if(kull_m_string_args_byName(argc, argv, L"in", &filename, NULL))
	{
		if(pXMLDom = kull_m_xml_CreateAndInitDOM())
		{
			if(kull_m_xml_LoadXMLFile(pXMLDom, filename))
			{
				if((IXMLDOMDocument_selectSingleNode(pXMLDom, (BSTR) L"//Objs/Obj", &pNode) == S_OK) && pNode)
				{
					if(kuhl_m_dpapi_powershell_check_against_one_type(pNode, L"System.Management.Automation.PSCredential") || kuhl_m_dpapi_powershell_check_against_one_type(pNode, L"System.Security.SecureString"))
						kuhl_m_dpapi_powershell_credential(pNode, argc, argv);
					else PRINT_ERROR(L"XML doesn't seem to be a PSCredential/SecureString\n");
				}
				else if((IXMLDOMDocument_selectSingleNode(pXMLDom, (BSTR) L"//Objs/SS", &pNode) == S_OK) && pNode)
					kuhl_m_dpapi_powershell_try_SecureString(pNode, argc, argv);
				else PRINT_ERROR(L"XML doesn't seem to be a SecureString\n");
			}
			kull_m_xml_ReleaseDom(pXMLDom);
		}
	}
	else PRINT_ERROR(L"Missing /in:credentials.xml\n");
	return STATUS_SUCCESS;
}