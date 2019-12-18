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
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IXMLDOMNode_get_firstChild (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNode_get_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_selectSingleNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

wchar_t * kull_m_xml_getTextValue(IXMLDOMNode *pNode, PCWSTR name)
{
	wchar_t *result = NULL;
	IXMLDOMNode *pSingleNode, *pChild;
	BSTR bstrGeneric;

	if((IXMLDOMNode_selectSingleNode(pNode, (BSTR) name, &pSingleNode) == S_OK) && pSingleNode)
	{
		if((IXMLDOMNode_get_firstChild(pSingleNode, &pChild) == S_OK) && pChild)
		{
			if(IXMLDOMNode_get_text(pChild, &bstrGeneric) == S_OK)
			{
				kull_m_string_copy(&result, bstrGeneric);
				SysFreeString(bstrGeneric);
			}
		}
	}
	return result;
}