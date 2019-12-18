#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int resumestate; int /*<<< orphan*/  nodetype; int /*<<< orphan*/  instate; int /*<<< orphan*/  elements; int /*<<< orphan*/  is_empty_element; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  StringValue_Prefix ; 
 int /*<<< orphan*/  StringValue_QualifiedName ; 
 int /*<<< orphan*/  StringValue_Value ; 
 int /*<<< orphan*/  XmlNodeType_Element ; 
 int /*<<< orphan*/  XmlReadInState_Content ; 
 int /*<<< orphan*/  XmlReadInState_MiscEnd ; 
#define  XmlReadResumeState_Initial 129 
#define  XmlReadResumeState_STag 128 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltW ; 
 int /*<<< orphan*/  reader_cmp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reader_parse_stag (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_set_strvalue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_shrink (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strval_empty ; 

__attribute__((used)) static HRESULT reader_parse_element(xmlreader *reader)
{
    HRESULT hr;

    switch (reader->resumestate)
    {
    case XmlReadResumeState_Initial:
        /* check if we are really on element */
        if (reader_cmp(reader, ltW)) return S_FALSE;

        /* skip '<' */
        reader_skipn(reader, 1);

        reader_shrink(reader);
        reader->resumestate = XmlReadResumeState_STag;
    case XmlReadResumeState_STag:
    {
        strval qname, prefix, local;

        /* this handles empty elements too */
        hr = reader_parse_stag(reader, &prefix, &local, &qname);
        if (FAILED(hr)) return hr;

        /* FIXME: need to check for defined namespace to reject invalid prefix */

        /* if we got empty element and stack is empty go straight to Misc */
        if (reader->is_empty_element && list_empty(&reader->elements))
            reader->instate = XmlReadInState_MiscEnd;
        else
            reader->instate = XmlReadInState_Content;

        reader->nodetype = XmlNodeType_Element;
        reader->resumestate = XmlReadResumeState_Initial;
        reader_set_strvalue(reader, StringValue_Prefix, &prefix);
        reader_set_strvalue(reader, StringValue_QualifiedName, &qname);
        reader_set_strvalue(reader, StringValue_Value, &strval_empty);
        break;
    }
    default:
        hr = E_FAIL;
    }

    return hr;
}