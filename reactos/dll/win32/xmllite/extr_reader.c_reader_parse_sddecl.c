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
typedef  char WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_E_QUOTE ; 
 int /*<<< orphan*/  WC_E_XMLDECL ; 
 char const* dblquoteW ; 
 int /*<<< orphan*/  debug_strval (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char const* quoteW ; 
 int /*<<< orphan*/  reader_add_attr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct reader_position*,int /*<<< orphan*/ ) ; 
 scalar_t__ reader_cmp (TYPE_1__*,char const*) ; 
 int reader_get_cur (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_init_strvalue (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_parse_eq (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  reader_skipspaces (TYPE_1__*) ; 

__attribute__((used)) static HRESULT reader_parse_sddecl(xmlreader *reader)
{
    static const WCHAR standaloneW[] = {'s','t','a','n','d','a','l','o','n','e',0};
    static const WCHAR yesW[] = {'y','e','s',0};
    static const WCHAR noW[] = {'n','o',0};
    struct reader_position position;
    strval name, val;
    UINT start;
    HRESULT hr;

    if (!reader_skipspaces(reader)) return S_FALSE;

    position = reader->position;
    if (reader_cmp(reader, standaloneW)) return S_FALSE;
    reader_init_strvalue(reader_get_cur(reader), 10, &name);
    /* skip 'standalone' */
    reader_skipn(reader, 10);

    hr = reader_parse_eq(reader);
    if (FAILED(hr)) return hr;

    if (reader_cmp(reader, quoteW) && reader_cmp(reader, dblquoteW))
        return WC_E_QUOTE;
    /* skip "'"|'"' */
    reader_skipn(reader, 1);

    if (reader_cmp(reader, yesW) && reader_cmp(reader, noW))
        return WC_E_XMLDECL;

    start = reader_get_cur(reader);
    /* skip 'yes'|'no' */
    reader_skipn(reader, reader_cmp(reader, yesW) ? 2 : 3);
    reader_init_strvalue(start, reader_get_cur(reader)-start, &val);
    TRACE("standalone=%s\n", debug_strval(reader, &val));

    if (reader_cmp(reader, quoteW) && reader_cmp(reader, dblquoteW))
        return WC_E_QUOTE;
    /* skip "'"|'"' */
    reader_skipn(reader, 1);

    return reader_add_attr(reader, NULL, &name, NULL, &val, &position, 0);
}