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
struct view {int dummy; } ;
struct parser {int /*<<< orphan*/  error; struct view** view; struct list* mem; scalar_t__ len; scalar_t__ idx; int /*<<< orphan*/  const* cmd; } ;
struct list {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  WBEM_E_INVALID_QUERY ; 
 int /*<<< orphan*/  destroy_view (struct view*) ; 
 int wql_parse (struct parser*) ; 

HRESULT parse_query( const WCHAR *str, struct view **view, struct list *mem )
{
    struct parser parser;
    int ret;

    *view = NULL;

    parser.cmd   = str;
    parser.idx   = 0;
    parser.len   = 0;
    parser.error = WBEM_E_INVALID_QUERY;
    parser.view  = view;
    parser.mem   = mem;

    ret = wql_parse( &parser );
    TRACE("wql_parse returned %d\n", ret);
    if (ret)
    {
        if (*parser.view)
        {
            destroy_view( *parser.view );
            *parser.view = NULL;
        }
        return parser.error;
    }
    return S_OK;
}