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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  DOMNodeType ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IXMLDOMDocument_selectSingleNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,long,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNodeList_get_length (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_nodeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_selectNodes (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  NODE_ELEMENT ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL kuhl_m_dpapi_powershell_check_against_one_type(IXMLDOMNode *pObj, LPCWSTR TypeName)
{
	BOOL status = FALSE;
	IXMLDOMNode *pNode, *pT;
	IXMLDOMNodeList *pTs;
	DOMNodeType type;
	long lengthT, i;
	BSTR bstrGeneric;

	if((IXMLDOMDocument_selectSingleNode(pObj, (BSTR) L"TN", &pNode) == S_OK) && pNode)
	{
		if((IXMLDOMNode_selectNodes(pNode, L"T", &pTs) == S_OK) && pTs)
		{
			if(IXMLDOMNodeList_get_length(pTs, &lengthT) == S_OK)
			{
				for(i = 0; (i < lengthT) && !status; i++)
				{
					if((IXMLDOMNodeList_get_item(pTs, i, &pT) == S_OK) && pT)
					{
						if((IXMLDOMNode_get_nodeType(pT, &type) == S_OK) && (type == NODE_ELEMENT))
						{
							if(IXMLDOMNode_get_text(pT, &bstrGeneric) == S_OK)
							{
								status = !_wcsicmp(bstrGeneric, TypeName);
								SysFreeString(bstrGeneric);
							}
						}
						IXMLDOMNode_Release(pT);
					}
				}
			}
		}
		else PRINT_ERROR(L"No types\n");
	}
	else PRINT_ERROR(L"No TN\n");
	return status;
}