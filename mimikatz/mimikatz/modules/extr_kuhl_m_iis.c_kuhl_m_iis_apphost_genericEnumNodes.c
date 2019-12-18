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
typedef  scalar_t__ PCWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPCBYTE ;
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int IISXMLType ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DOMNodeType ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  IISXMLType_ApplicationPools 130 
#define  IISXMLType_Providers 129 
#define  IISXMLType_Sites 128 
 scalar_t__ IXMLDOMDocument_selectNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,long,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNodeList_get_length (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_nodeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NODE_ELEMENT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  kuhl_m_iis_apphost_apppool (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_iis_apphost_provider (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_iis_apphost_site (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void kuhl_m_iis_apphost_genericEnumNodes(int argc, wchar_t * argv[], IXMLDOMDocument *pXMLDom, PCWSTR path, IISXMLType xmltype, LPCWSTR provider, LPCBYTE data, DWORD szData)
{
	IXMLDOMNodeList *pNodes;
	IXMLDOMNode *pNode;
	DOMNodeType type;
	BOOL mustBreak = FALSE;
	long length, i;

	if((IXMLDOMDocument_selectNodes(pXMLDom, (BSTR) path, &pNodes) == S_OK) && pNodes)
	{
		if(IXMLDOMNodeList_get_length(pNodes, &length) == S_OK)
		{
			for(i = 0; (i < length) && !mustBreak; i++)
			{
				if((IXMLDOMNodeList_get_item(pNodes, i, &pNode) == S_OK) && pNode)
				{
					if((IXMLDOMNode_get_nodeType(pNode, &type) == S_OK) && (type == NODE_ELEMENT))
					{
						switch(xmltype)
						{
						case IISXMLType_ApplicationPools:
							kuhl_m_iis_apphost_apppool(argc, argv, pXMLDom, pNode);
							break;
						case IISXMLType_Sites:
							kuhl_m_iis_apphost_site(argc, argv, pXMLDom, pNode);
							break;
						case IISXMLType_Providers:
							mustBreak = kuhl_m_iis_apphost_provider(argc, argv, pXMLDom, pNode, provider, data, szData);
							break;
						}
					}
					IXMLDOMNode_Release(pNode);
				}
			}
		}
	}
}