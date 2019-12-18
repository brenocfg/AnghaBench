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
struct gc_arena {int dummy; } ;

/* Variables and functions */
 char* gc_malloc (size_t,int,struct gc_arena*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 char* string_alloc (char const*,struct gc_arena*) ; 

__attribute__((used)) static char *
get_ipv6_addr_no_netbits(const char *addr, struct gc_arena *gc)
{
    const char *end = strchr(addr, '/');
    char *ret = NULL;
    if (NULL == end)
    {
        ret = string_alloc(addr, gc);
    }
    else
    {
        size_t len = end - addr;
        ret = gc_malloc(len + 1, true, gc);
        memcpy(ret, addr, len);
    }
    return ret;
}