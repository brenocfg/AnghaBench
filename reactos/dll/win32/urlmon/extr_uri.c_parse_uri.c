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
struct TYPE_8__ {int /*<<< orphan*/ * uri; } ;
typedef  TYPE_1__ parse_data ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_fragment (int /*<<< orphan*/  const**,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_hierpart (int /*<<< orphan*/  const**,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_query (int /*<<< orphan*/  const**,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_scheme (int /*<<< orphan*/  const**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL parse_uri(parse_data *data, DWORD flags) {
    const WCHAR *ptr;
    const WCHAR **pptr;

    ptr = data->uri;
    pptr = &ptr;

    TRACE("(%p %x): BEGINNING TO PARSE URI %s.\n", data, flags, debugstr_w(data->uri));

    if(!parse_scheme(pptr, data, flags, 0))
        return FALSE;

    if(!parse_hierpart(pptr, data, flags))
        return FALSE;

    if(!parse_query(pptr, data, flags))
        return FALSE;

    if(!parse_fragment(pptr, data, flags))
        return FALSE;

    TRACE("(%p %x): FINISHED PARSING URI.\n", data, flags);
    return TRUE;
}