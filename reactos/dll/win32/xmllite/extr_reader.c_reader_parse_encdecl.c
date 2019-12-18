#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct reader_position {int dummy; } ;
struct TYPE_15__ {struct reader_position position; } ;
typedef  TYPE_1__ xmlreader ;
struct TYPE_16__ {int len; int /*<<< orphan*/  start; int /*<<< orphan*/  str; } ;
typedef  TYPE_2__ strval ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  WC_E_QUOTE ; 
 char const* dblquoteW ; 
 char const* quoteW ; 
 int /*<<< orphan*/  reader_add_attr (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*,struct reader_position*,int /*<<< orphan*/ ) ; 
 scalar_t__ reader_cmp (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  reader_get_cur (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_get_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_encname (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  reader_parse_eq (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  reader_skipspaces (TYPE_1__*) ; 

__attribute__((used)) static HRESULT reader_parse_encdecl(xmlreader *reader)
{
    static const WCHAR encodingW[] = {'e','n','c','o','d','i','n','g',0};
    struct reader_position position;
    strval name, val;
    HRESULT hr;

    if (!reader_skipspaces(reader)) return S_FALSE;

    position = reader->position;
    if (reader_cmp(reader, encodingW)) return S_FALSE;
    name.str = reader_get_ptr(reader);
    name.start = reader_get_cur(reader);
    name.len = 8;
    /* skip 'encoding' */
    reader_skipn(reader, 8);

    hr = reader_parse_eq(reader);
    if (FAILED(hr)) return hr;

    if (reader_cmp(reader, quoteW) && reader_cmp(reader, dblquoteW))
        return WC_E_QUOTE;
    /* skip "'"|'"' */
    reader_skipn(reader, 1);

    hr = reader_parse_encname(reader, &val);
    if (FAILED(hr)) return hr;

    if (reader_cmp(reader, quoteW) && reader_cmp(reader, dblquoteW))
        return WC_E_QUOTE;

    /* skip "'"|'"' */
    reader_skipn(reader, 1);

    return reader_add_attr(reader, NULL, &name, NULL, &val, &position, 0);
}