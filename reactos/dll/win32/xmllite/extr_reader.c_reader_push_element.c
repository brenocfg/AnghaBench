#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  is_empty_element; int /*<<< orphan*/  elements; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
struct reader_position {int dummy; } ;
struct element {struct reader_position position; int /*<<< orphan*/  entry; int /*<<< orphan*/  qname; int /*<<< orphan*/  localname; int /*<<< orphan*/  prefix; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct element* reader_alloc_zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  reader_free_element (TYPE_1__*,struct element*) ; 
 int /*<<< orphan*/  reader_mark_ns_nodes (TYPE_1__*,struct element*) ; 
 int /*<<< orphan*/  reader_strvaldup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT reader_push_element(xmlreader *reader, strval *prefix, strval *localname,
    strval *qname, const struct reader_position *position)
{
    struct element *element;
    HRESULT hr;

    element = reader_alloc_zero(reader, sizeof(*element));
    if (!element)
        return E_OUTOFMEMORY;

    if ((hr = reader_strvaldup(reader, prefix, &element->prefix)) == S_OK &&
            (hr = reader_strvaldup(reader, localname, &element->localname)) == S_OK &&
            (hr = reader_strvaldup(reader, qname, &element->qname)) == S_OK)
    {
        list_add_head(&reader->elements, &element->entry);
        reader_mark_ns_nodes(reader, element);
        reader->is_empty_element = FALSE;
        element->position = *position;
    }
    else
        reader_free_element(reader, element);

    return hr;
}