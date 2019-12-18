#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  host_type; } ;
typedef  TYPE_1__ parse_data ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,char const**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Uri_HOST_UNKNOWN ; 
 int /*<<< orphan*/  debugstr_wn (char const*,int) ; 
 scalar_t__ is_hexdigit (char const) ; 
 scalar_t__ is_subdelim (char const) ; 
 scalar_t__ is_unreserved (char const) ; 

__attribute__((used)) static BOOL parse_ipvfuture(const WCHAR **ptr, parse_data *data, DWORD flags) {
    const WCHAR *start = *ptr;

    /* IPvFuture has to start with a 'v' or 'V'. */
    if(**ptr != 'v' && **ptr != 'V')
        return FALSE;

    /* Following the v there must be at least 1 hex digit. */
    ++(*ptr);
    if(!is_hexdigit(**ptr)) {
        *ptr = start;
        return FALSE;
    }

    ++(*ptr);
    while(is_hexdigit(**ptr))
        ++(*ptr);

    /* End of the hexdigit sequence must be a '.' */
    if(**ptr != '.') {
        *ptr = start;
        return FALSE;
    }

    ++(*ptr);
    if(!is_unreserved(**ptr) && !is_subdelim(**ptr) && **ptr != ':') {
        *ptr = start;
        return FALSE;
    }

    ++(*ptr);
    while(is_unreserved(**ptr) || is_subdelim(**ptr) || **ptr == ':')
        ++(*ptr);

    data->host_type = Uri_HOST_UNKNOWN;

    TRACE("(%p %p %x): Parsed IPvFuture address %s len=%d\n", ptr, data, flags,
          debugstr_wn(start, *ptr-start), (int)(*ptr-start));

    return TRUE;
}