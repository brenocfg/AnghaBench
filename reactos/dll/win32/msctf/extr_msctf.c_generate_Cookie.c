#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_6__ {size_t id; size_t magic; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  size_t DWORD ;
typedef  TYPE_1__ CookieInternal ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 size_t array_size ; 
 TYPE_1__* cookies ; 
 size_t id_last ; 

DWORD generate_Cookie(DWORD magic, LPVOID data)
{
    UINT i;

    /* try to reuse IDs if possible */
    for (i = 0; i < id_last; i++)
        if (cookies[i].id == 0) break;

    if (i == array_size)
    {
        if (!array_size)
        {
            cookies = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(CookieInternal) * 10);
            if (!cookies)
            {
                ERR("Out of memory, Unable to alloc cookies array\n");
                return 0;
            }
            array_size = 10;
        }
        else
        {
            CookieInternal *new_cookies = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cookies,
                                                      sizeof(CookieInternal) * (array_size * 2));
            if (!new_cookies)
            {
                ERR("Out of memory, Unable to realloc cookies array\n");
                return 0;
            }
            cookies = new_cookies;
            array_size *= 2;
        }
    }

    cookies[i].id = i + 1; /* a return of 0 is used for failure */
    cookies[i].magic = magic;
    cookies[i].data = data;

    if (i == id_last)
        id_last++;

    return cookies[i].id;
}