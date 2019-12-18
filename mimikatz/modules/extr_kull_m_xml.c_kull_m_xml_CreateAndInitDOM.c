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
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_DOMDocument ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMDocument_put_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXMLDOMDocument_put_preserveWhiteSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXMLDOMDocument_put_resolveExternals (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXMLDOMDocument_put_validateOnParse (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 

IXMLDOMDocument * kull_m_xml_CreateAndInitDOM()
{
	IXMLDOMDocument *pDoc = NULL;
	HRESULT hr = CoCreateInstance(&CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER, &IID_IXMLDOMDocument, (void **) &pDoc);
	if(hr == S_OK)
	{
		IXMLDOMDocument_put_async(pDoc, VARIANT_FALSE);  
		IXMLDOMDocument_put_validateOnParse(pDoc, VARIANT_FALSE);
		IXMLDOMDocument_put_resolveExternals(pDoc, VARIANT_FALSE);
		IXMLDOMDocument_put_preserveWhiteSpace(pDoc, VARIANT_FALSE);
	}
	else PRINT_ERROR(L"CoCreateInstance: 0x%08x\n", hr);
	return pDoc;
}