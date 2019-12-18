#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ dtdmode; int /*<<< orphan*/  nodetype; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ DtdProcessing_Prohibit ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringValue_LocalName ; 
 int /*<<< orphan*/  StringValue_QualifiedName ; 
 int /*<<< orphan*/  WC_E_DECLDOCTYPE ; 
 int /*<<< orphan*/  WC_E_DTDPROHIBITED ; 
 int /*<<< orphan*/  WC_E_WHITESPACE ; 
 int /*<<< orphan*/  XmlNodeType_DocumentType ; 
 scalar_t__ reader_cmp (TYPE_1__*,char const*) ; 
 char* reader_get_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_externalid (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_name (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_set_strvalue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_shrink (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  reader_skipspaces (TYPE_1__*) ; 

__attribute__((used)) static HRESULT reader_parse_dtd(xmlreader *reader)
{
    static const WCHAR doctypeW[] = {'<','!','D','O','C','T','Y','P','E',0};
    strval name;
    WCHAR *cur;
    HRESULT hr;

    /* check if we have "<!DOCTYPE" */
    if (reader_cmp(reader, doctypeW)) return S_FALSE;
    reader_shrink(reader);

    /* DTD processing is not allowed by default */
    if (reader->dtdmode == DtdProcessing_Prohibit) return WC_E_DTDPROHIBITED;

    reader_skipn(reader, 9);
    if (!reader_skipspaces(reader)) return WC_E_WHITESPACE;

    /* name */
    hr = reader_parse_name(reader, &name);
    if (FAILED(hr)) return WC_E_DECLDOCTYPE;

    reader_skipspaces(reader);

    hr = reader_parse_externalid(reader);
    if (FAILED(hr)) return hr;

    reader_skipspaces(reader);

    cur = reader_get_ptr(reader);
    if (*cur != '>')
    {
        FIXME("internal subset parsing not implemented\n");
        return E_NOTIMPL;
    }

    /* skip '>' */
    reader_skipn(reader, 1);

    reader->nodetype = XmlNodeType_DocumentType;
    reader_set_strvalue(reader, StringValue_LocalName, &name);
    reader_set_strvalue(reader, StringValue_QualifiedName, &name);

    return S_OK;
}