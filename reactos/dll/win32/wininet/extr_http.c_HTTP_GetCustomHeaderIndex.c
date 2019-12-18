#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t nCustHeaders; TYPE_1__* custHeaders; } ;
typedef  TYPE_2__ http_request_t ;
struct TYPE_4__ {int wFlags; int /*<<< orphan*/  lpszField; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  size_t INT ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int HDR_ISREQUEST ; 
 int /*<<< orphan*/  TRACE (char*,size_t,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT HTTP_GetCustomHeaderIndex(http_request_t *request, LPCWSTR lpszField,
                                     int requested_index, BOOL request_only)
{
    DWORD index;

    TRACE("%s, %d, %d\n", debugstr_w(lpszField), requested_index, request_only);

    for (index = 0; index < request->nCustHeaders; index++)
    {
        if (strcmpiW(request->custHeaders[index].lpszField, lpszField))
            continue;

        if (request_only && !(request->custHeaders[index].wFlags & HDR_ISREQUEST))
            continue;

        if (!request_only && (request->custHeaders[index].wFlags & HDR_ISREQUEST))
            continue;

        if (requested_index == 0)
            break;
        requested_index --;
    }

    if (index >= request->nCustHeaders)
	index = -1;

    TRACE("Return: %d\n", index);
    return index;
}