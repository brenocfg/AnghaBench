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
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMNamedNodeMap ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  IXMLDOMNamedNodeMap_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNamedNodeMap_get_item (int /*<<< orphan*/ *,long,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNamedNodeMap_get_length (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNode_get_nodeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

wchar_t * kull_m_xml_getAttribute(IXMLDOMNode *pNode, PCWSTR name)
{
	wchar_t *result = NULL;
	IXMLDOMNamedNodeMap *map;
	IXMLDOMNode *nAttr;
	BSTR bstrGeneric;
	long length, i;
	BOOL isMatch = FALSE;

	if(IXMLDOMNode_get_attributes(pNode, &map) == S_OK)
	{
		if(IXMLDOMNamedNodeMap_get_length(map, &length) == S_OK)
		{
			for(i = 0; (i < length) && !isMatch; i++)
			{
				if(IXMLDOMNamedNodeMap_get_item(map, i, &nAttr) == S_OK)
				{
					if(IXMLDOMNode_get_nodeName(nAttr, &bstrGeneric) == S_OK)
					{
						isMatch = (_wcsicmp(name, bstrGeneric) == 0);
						SysFreeString(bstrGeneric);
						if(isMatch)
						{
							if(IXMLDOMNode_get_text(nAttr, &bstrGeneric) == S_OK)
							{
								kull_m_string_copy(&result, bstrGeneric);
								SysFreeString(bstrGeneric);
							}
						}
					}
					IXMLDOMNode_Release(nAttr);
				}
			}
		}
		IXMLDOMNamedNodeMap_Release(map);
	}
	return result;
}