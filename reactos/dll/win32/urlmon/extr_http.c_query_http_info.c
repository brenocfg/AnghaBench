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
struct TYPE_4__ {int /*<<< orphan*/  request; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  TYPE_2__ HttpProtocol ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ HttpQueryInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * heap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LPWSTR query_http_info(HttpProtocol *This, DWORD option)
{
    LPWSTR ret = NULL;
    DWORD len = 0;
    BOOL res;

    res = HttpQueryInfoW(This->base.request, option, NULL, &len, NULL);
    if (!res && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
        ret = heap_alloc(len);
        res = HttpQueryInfoW(This->base.request, option, ret, &len, NULL);
    }
    if(!res) {
        TRACE("HttpQueryInfoW(%d) failed: %08x\n", option, GetLastError());
        heap_free(ret);
        return NULL;
    }

    return ret;
}