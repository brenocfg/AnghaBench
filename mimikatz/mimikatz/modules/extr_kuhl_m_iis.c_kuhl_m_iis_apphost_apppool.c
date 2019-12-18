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
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;

/* Variables and functions */
 scalar_t__ IXMLDOMNode_selectSingleNode (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_iis_maybeEncrypted (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_xml_getAttribute (int /*<<< orphan*/ *,char*) ; 

void kuhl_m_iis_apphost_apppool(int argc, wchar_t * argv[], IXMLDOMDocument *pXMLDom, IXMLDOMNode *pNode)
{
	PWSTR gen;
	IXMLDOMNode *pProcessModelNode;
	if(gen = kull_m_xml_getAttribute(pNode, L"name"))
	{
		kprintf(L"\n* ApplicationPool: \'%s\'\n", gen);
		LocalFree(gen);
		if((IXMLDOMNode_selectSingleNode(pNode, L"processModel", &pProcessModelNode) == S_OK) && pProcessModelNode)
		{
			if(gen = kull_m_xml_getAttribute(pProcessModelNode, L"userName"))
			{
				kprintf(L"  Username: %s\n", gen);
				LocalFree(gen);
				if(gen = kull_m_xml_getAttribute(pProcessModelNode, L"password"))
				{
					kprintf(L"  Password: %s\n", gen);
					kuhl_m_iis_maybeEncrypted(argc, argv, pXMLDom, gen);
					LocalFree(gen);
				}
			}
		}
	}
}