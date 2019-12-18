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
typedef  int /*<<< orphan*/  DOMNodeType ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IXMLDOMDocument_selectSingleNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,long,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNodeList_get_length (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_childNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNode_get_nodeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NODE_ELEMENT ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_powershell_try_SecureString (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * kull_m_xml_getAttribute (int /*<<< orphan*/ *,char*) ; 

void kuhl_m_dpapi_powershell_credential(IXMLDOMNode *pObj, int argc, wchar_t * argv[])
{
	IXMLDOMNode *pNode, *pChild;
	IXMLDOMNodeList *pChilds;
	long listLength, i;
	DOMNodeType type;
	wchar_t *name;

	if((IXMLDOMDocument_selectSingleNode(pObj, (BSTR) L"Props", &pNode) == S_OK) && pNode)
	{
		if(IXMLDOMNode_get_childNodes(pNode, &pChilds) == S_OK)
		{
			if(IXMLDOMNodeList_get_length(pChilds, &listLength) == S_OK)
			{
				for(i = 0; i < listLength; i++)
				{
					if((IXMLDOMNodeList_get_item(pChilds, i, &pChild) == S_OK) && pChild)
					{
						if((IXMLDOMNode_get_nodeType(pChild, &type) == S_OK) && (type == NODE_ELEMENT))
						{
							if(name = kull_m_xml_getAttribute(pChild, L"N"))
							{
								kprintf(L"%s: ", name);
								LocalFree(name);
								kuhl_m_dpapi_powershell_try_SecureString(pChild, argc, argv);
							}
							else PRINT_ERROR(L"No NAME\n");
						}
						else PRINT_ERROR(L"Not ELEMENT\n");
						IXMLDOMNode_Release(pChild);
					}
				}
			}
			IXMLDOMNodeList_Release(pChilds);
		}
	}
	else PRINT_ERROR(L"No Props\n");
}