#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int line_number; int line_position; } ;
struct TYPE_19__ {int instate; int /*<<< orphan*/  nodetype; int /*<<< orphan*/  state; int /*<<< orphan*/  input; TYPE_1__ position; int /*<<< orphan*/  empty_element; int /*<<< orphan*/  is_empty_element; scalar_t__ chunk_read_off; } ;
typedef  TYPE_2__ xmlreader ;
typedef  size_t xml_encoding ;
typedef  int XmlNodeType ;
struct TYPE_20__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WC_E_SYNTAX ; 
 size_t XmlEncoding_Unknown ; 
#define  XmlNodeType_Attribute 138 
#define  XmlNodeType_Element 137 
#define  XmlNodeType_EndElement 136 
 int /*<<< orphan*/  XmlNodeType_None ; 
#define  XmlReadInState_Content 135 
#define  XmlReadInState_DTD 134 
#define  XmlReadInState_DTD_Misc 133 
#define  XmlReadInState_Element 132 
#define  XmlReadInState_Eof 131 
#define  XmlReadInState_Initial 130 
#define  XmlReadInState_MiscEnd 129 
#define  XmlReadInState_Misc_DTD 128 
 int /*<<< orphan*/  XmlReadState_EndOfFile ; 
 char* debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_reader_pending (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_clear_attrs (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_dec_depth (TYPE_2__*) ; 
 int reader_get_nodetype (TYPE_2__*) ; 
 int /*<<< orphan*/ * reader_get_ptr (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_inc_depth (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_parse_content (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_parse_dtd (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_parse_element (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_parse_misc (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_parse_xmldecl (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_pop_element (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_pop_ns_nodes (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readerinput_detectencoding (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  readerinput_growraw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readerinput_shrinkraw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readerinput_switchencoding (int /*<<< orphan*/ ,size_t) ; 
 TYPE_3__* xml_encoding_map ; 

__attribute__((used)) static HRESULT reader_parse_nextnode(xmlreader *reader)
{
    XmlNodeType nodetype = reader_get_nodetype(reader);
    HRESULT hr;

    if (!is_reader_pending(reader))
    {
        reader->chunk_read_off = 0;
        reader_clear_attrs(reader);
    }

    /* When moving from EndElement or empty element, pop its own namespace definitions */
    switch (nodetype)
    {
    case XmlNodeType_Attribute:
        reader_dec_depth(reader);
        /* fallthrough */
    case XmlNodeType_Element:
        if (reader->is_empty_element)
            reader_pop_ns_nodes(reader, &reader->empty_element);
        else if (FAILED(hr = reader_inc_depth(reader)))
            return hr;
        break;
    case XmlNodeType_EndElement:
        reader_pop_element(reader);
        reader_dec_depth(reader);
        break;
    default:
        ;
    }

    for (;;)
    {
        switch (reader->instate)
        {
        /* if it's a first call for a new input we need to detect stream encoding */
        case XmlReadInState_Initial:
            {
                xml_encoding enc;

                hr = readerinput_growraw(reader->input);
                if (FAILED(hr)) return hr;

                reader->position.line_number = 1;
                reader->position.line_position = 1;

                /* try to detect encoding by BOM or data and set input code page */
                hr = readerinput_detectencoding(reader->input, &enc);
                TRACE("detected encoding %s, 0x%08x\n", enc == XmlEncoding_Unknown ? "(unknown)" :
                        debugstr_w(xml_encoding_map[enc].name), hr);
                if (FAILED(hr)) return hr;

                /* always switch first time cause we have to put something in */
                readerinput_switchencoding(reader->input, enc);

                /* parse xml declaration */
                hr = reader_parse_xmldecl(reader);
                if (FAILED(hr)) return hr;

                readerinput_shrinkraw(reader->input, -1);
                reader->instate = XmlReadInState_Misc_DTD;
                if (hr == S_OK) return hr;
            }
            break;
        case XmlReadInState_Misc_DTD:
            hr = reader_parse_misc(reader);
            if (FAILED(hr)) return hr;

            if (hr == S_FALSE)
                reader->instate = XmlReadInState_DTD;
            else
                return hr;
            break;
        case XmlReadInState_DTD:
            hr = reader_parse_dtd(reader);
            if (FAILED(hr)) return hr;

            if (hr == S_OK)
            {
                reader->instate = XmlReadInState_DTD_Misc;
                return hr;
            }
            else
                reader->instate = XmlReadInState_Element;
            break;
        case XmlReadInState_DTD_Misc:
            hr = reader_parse_misc(reader);
            if (FAILED(hr)) return hr;

            if (hr == S_FALSE)
                reader->instate = XmlReadInState_Element;
            else
                return hr;
            break;
        case XmlReadInState_Element:
            return reader_parse_element(reader);
        case XmlReadInState_Content:
            return reader_parse_content(reader);
        case XmlReadInState_MiscEnd:
            hr = reader_parse_misc(reader);
            if (hr != S_FALSE) return hr;

            if (*reader_get_ptr(reader))
            {
                WARN("found garbage in the end of XML\n");
                return WC_E_SYNTAX;
            }

            reader->instate = XmlReadInState_Eof;
            reader->state = XmlReadState_EndOfFile;
            reader->nodetype = XmlNodeType_None;
            return hr;
        case XmlReadInState_Eof:
            return S_FALSE;
        default:
            FIXME("internal state %d not handled\n", reader->instate);
            return E_NOTIMPL;
        }
    }

    return E_NOTIMPL;
}