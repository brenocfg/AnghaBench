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
struct in_addr {scalar_t__ s_addr; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;
typedef  scalar_t__ in_addr_t ;

/* Variables and functions */
 char const* BSTR (struct buffer*) ; 
 int /*<<< orphan*/  CLEAR (struct in_addr) ; 
 unsigned int IA_EMPTY_IF_UNDEF ; 
 unsigned int IA_NET_ORDER ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ htonl (scalar_t__) ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 

const char *
print_in_addr_t(in_addr_t addr, unsigned int flags, struct gc_arena *gc)
{
    struct in_addr ia;
    struct buffer out = alloc_buf_gc(64, gc);

    if (addr || !(flags & IA_EMPTY_IF_UNDEF))
    {
        CLEAR(ia);
        ia.s_addr = (flags & IA_NET_ORDER) ? addr : htonl(addr);

        buf_printf(&out, "%s", inet_ntoa(ia));
    }
    return BSTR(&out);
}