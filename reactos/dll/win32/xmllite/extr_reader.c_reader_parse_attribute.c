#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct reader_position {int dummy; } ;
struct TYPE_10__ {struct reader_position position; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  enum attribute_flags { ____Placeholder_attribute_flags } attribute_flags ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int ATTRIBUTE_DEFAULT_NS_DEFINITION ; 
 int ATTRIBUTE_NS_DEFINITION ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_strval (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_add_attr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct reader_position*,int) ; 
 int /*<<< orphan*/  reader_parse_attvalue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_parse_eq (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_qname (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_push_ns (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strval_eq (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strval_xmlns ; 

__attribute__((used)) static HRESULT reader_parse_attribute(xmlreader *reader)
{
    struct reader_position position = reader->position;
    strval prefix, local, qname, value;
    enum attribute_flags flags = 0;
    HRESULT hr;

    hr = reader_parse_qname(reader, &prefix, &local, &qname);
    if (FAILED(hr)) return hr;

    if (strval_eq(reader, &prefix, &strval_xmlns))
        flags |= ATTRIBUTE_NS_DEFINITION;

    if (strval_eq(reader, &qname, &strval_xmlns))
        flags |= ATTRIBUTE_DEFAULT_NS_DEFINITION;

    hr = reader_parse_eq(reader);
    if (FAILED(hr)) return hr;

    hr = reader_parse_attvalue(reader, &value);
    if (FAILED(hr)) return hr;

    if (flags & (ATTRIBUTE_NS_DEFINITION | ATTRIBUTE_DEFAULT_NS_DEFINITION))
        reader_push_ns(reader, &local, &value, !!(flags & ATTRIBUTE_DEFAULT_NS_DEFINITION));

    TRACE("%s=%s\n", debug_strval(reader, &local), debug_strval(reader, &value));
    return reader_add_attr(reader, &prefix, &local, &qname, &value, &position, flags);
}