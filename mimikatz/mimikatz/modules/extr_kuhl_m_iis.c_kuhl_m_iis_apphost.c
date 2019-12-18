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
typedef  int /*<<< orphan*/  IXMLDOMDocument ;

/* Variables and functions */
 int /*<<< orphan*/  IISXMLType_ApplicationPools ; 
 int /*<<< orphan*/  IISXMLType_Sites ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kuhl_m_iis_apphost_genericEnumNodes (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kull_m_xml_CreateAndInitDOM () ; 
 scalar_t__ kull_m_xml_LoadXMLFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_xml_ReleaseDom (int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_iis_apphost(int argc, wchar_t * argv[])
{
	PCWSTR filename;
	IXMLDOMDocument *pXMLDom;

	if(kull_m_string_args_byName(argc, argv, L"in", &filename, NULL))
	{
		if(pXMLDom = kull_m_xml_CreateAndInitDOM())
		{
			if(kull_m_xml_LoadXMLFile(pXMLDom, filename))
			{
				kuhl_m_iis_apphost_genericEnumNodes(argc, argv, pXMLDom, L"//configuration/system.applicationHost/applicationPools/add", IISXMLType_ApplicationPools, NULL, NULL, 0);
				kuhl_m_iis_apphost_genericEnumNodes(argc, argv, pXMLDom, L"//configuration/system.applicationHost/sites/site", IISXMLType_Sites, NULL, NULL, 0);
			}
			kull_m_xml_ReleaseDom(pXMLDom);
		}
	}
	else PRINT_ERROR(L"Missing /in:filename (applicationHost.config)\n");
	return STATUS_SUCCESS;
}