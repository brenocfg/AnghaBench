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
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DOMNodeType ;

/* Variables and functions */
 scalar_t__ IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,long,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNodeList_get_length (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_nodeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_selectNodes (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNode_selectSingleNode (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NODE_ELEMENT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  kprintf (char*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_rdg_LogonCredentials (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_rdg_Servers (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * kull_m_xml_getTextValue (int /*<<< orphan*/ *,char*) ; 

void kuhl_m_dpapi_rdg_Groups(DWORD level, IXMLDOMNode *pNode, int argc, wchar_t * argv[])
{
	IXMLDOMNodeList *pGroups;
	IXMLDOMNode *pGroup, *pProperties;
	DOMNodeType type;
	long lengthGroups, i;
	wchar_t *name;

	kuhl_m_dpapi_rdg_LogonCredentials(level, pNode, argc, argv);
	kuhl_m_dpapi_rdg_Servers(level, pNode, argc, argv);
	if((IXMLDOMNode_selectNodes(pNode, L"group", &pGroups) == S_OK) && pGroups)
	{
		if(IXMLDOMNodeList_get_length(pGroups, &lengthGroups) == S_OK)
		{
			for(i = 0; i < lengthGroups; i++)
			{
				if((IXMLDOMNodeList_get_item(pGroups, i, &pGroup) == S_OK) && pGroup)
				{
					if((IXMLDOMNode_get_nodeType(pGroup, &type) == S_OK) && (type == NODE_ELEMENT))
					{
						if((IXMLDOMNode_selectSingleNode(pGroup, L"properties", &pProperties) == S_OK) && pProperties)
						{
							if(name = kull_m_xml_getTextValue(pProperties, L"name"))
							{
								kprintf(L"%*s" L"<%s>\n", level << 1, L"", name);
								LocalFree(name);
							}
						}
						kuhl_m_dpapi_rdg_Groups(level + 1, pGroup, argc, argv);
					}
					IXMLDOMNode_Release(pGroup);
				}
			}
		}
	}
}