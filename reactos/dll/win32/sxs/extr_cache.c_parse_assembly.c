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
struct assembly {void* type; void* token; void* arch; void* version; void* name; int /*<<< orphan*/  files; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMNamedNodeMap ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ ERROR_SXS_MANIFEST_FORMAT_ERROR ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct assembly* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IXMLDOMDocument_getElementsByTagName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNamedNodeMap_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNodeList_get_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNodeList_nextNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  free_assembly (struct assembly*) ; 
 void* get_attribute_value (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_files (int /*<<< orphan*/ *,struct assembly*) ; 
 scalar_t__ strcmpW (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win32W ; 
 int /*<<< orphan*/  win32_policyW ; 

__attribute__((used)) static HRESULT parse_assembly( IXMLDOMDocument *doc, struct assembly **assembly )
{
    static const WCHAR identityW[] = {'a','s','s','e','m','b','l','y','I','d','e','n','t','i','t','y',0};
    static const WCHAR typeW[] = {'t','y','p','e',0};
    static const WCHAR nameW[] = {'n','a','m','e',0};
    static const WCHAR versionW[] = {'v','e','r','s','i','o','n',0};
    static const WCHAR architectureW[] = {'p','r','o','c','e','s','s','o','r','A','r','c','h','i','t','e','c','t','u','r','e',0};
    static const WCHAR tokenW[] = {'p','u','b','l','i','c','K','e','y','T','o','k','e','n',0};
    IXMLDOMNodeList *list = NULL;
    IXMLDOMNode *node = NULL;
    IXMLDOMNamedNodeMap *attrs = NULL;
    struct assembly *a = NULL;
    BSTR str;
    HRESULT hr;
    LONG len;

    str = SysAllocString( identityW );
    hr = IXMLDOMDocument_getElementsByTagName( doc, str, &list );
    SysFreeString( str );
    if (hr != S_OK) goto done;

    hr = IXMLDOMNodeList_get_length( list, &len );
    if (hr != S_OK) goto done;
    if (!len)
    {
        hr = ERROR_SXS_MANIFEST_FORMAT_ERROR;
        goto done;
    }
    hr = IXMLDOMNodeList_nextNode( list, &node );
    if (hr != S_OK) goto done;
    if (!node)
    {
        hr = ERROR_SXS_MANIFEST_FORMAT_ERROR;
        goto done;
    }
    if (!(a = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(struct assembly) )))
    {
        hr = E_OUTOFMEMORY;
        goto done;
    }
    list_init( &a->files );

    hr = IXMLDOMNode_get_attributes( node, &attrs );
    if (hr != S_OK) goto done;

    a->type    = get_attribute_value( attrs, typeW );
    a->name    = get_attribute_value( attrs, nameW );
    a->version = get_attribute_value( attrs, versionW );
    a->arch    = get_attribute_value( attrs, architectureW );
    a->token   = get_attribute_value( attrs, tokenW );

    if (!a->type || (strcmpW( a->type, win32W ) && strcmpW( a->type, win32_policyW )) ||
        !a->name || !a->version || !a->arch || !a->token)
    {
        WARN("invalid win32 assembly\n");
        hr = ERROR_SXS_MANIFEST_FORMAT_ERROR;
        goto done;
    }
    if (!strcmpW( a->type, win32W )) hr = parse_files( doc, a );

done:
    if (attrs) IXMLDOMNamedNodeMap_Release( attrs );
    if (node) IXMLDOMNode_Release( node );
    if (list) IXMLDOMNodeList_Release( list );
    if (hr == S_OK) *assembly = a;
    else free_assembly( a );
    return hr;
}