#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct reader_position {int dummy; } ;
struct element {struct reader_position position; int /*<<< orphan*/  localname; int /*<<< orphan*/  qname; int /*<<< orphan*/  prefix; } ;
struct TYPE_12__ {int is_empty_element; struct element empty_element; struct reader_position position; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 char const* gtW ; 
 int /*<<< orphan*/  reader_cmp (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  reader_free_strvalued (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_mark_ns_nodes (TYPE_1__*,struct element*) ; 
 int /*<<< orphan*/  reader_parse_attribute (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_qname (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_push_element (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct reader_position*) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  reader_skipspaces (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_strvaldup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT reader_parse_stag(xmlreader *reader, strval *prefix, strval *local, strval *qname)
{
    struct reader_position position = reader->position;
    HRESULT hr;

    hr = reader_parse_qname(reader, prefix, local, qname);
    if (FAILED(hr)) return hr;

    for (;;)
    {
        static const WCHAR endW[] = {'/','>',0};

        reader_skipspaces(reader);

        /* empty element */
        if ((reader->is_empty_element = !reader_cmp(reader, endW)))
        {
            struct element *element = &reader->empty_element;

            /* skip '/>' */
            reader_skipn(reader, 2);

            reader_free_strvalued(reader, &element->qname);
            reader_free_strvalued(reader, &element->localname);

            element->prefix = *prefix;
            reader_strvaldup(reader, qname, &element->qname);
            reader_strvaldup(reader, local, &element->localname);
            element->position = position;
            reader_mark_ns_nodes(reader, element);
            return S_OK;
        }

        /* got a start tag */
        if (!reader_cmp(reader, gtW))
        {
            /* skip '>' */
            reader_skipn(reader, 1);
            return reader_push_element(reader, prefix, local, qname, &position);
        }

        hr = reader_parse_attribute(reader);
        if (FAILED(hr)) return hr;
    }

    return S_OK;
}