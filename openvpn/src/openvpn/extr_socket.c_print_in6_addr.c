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
typedef  int /*<<< orphan*/  tmp_out_buf ;
struct in6_addr {int dummy; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  a6 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 char const* BSTR (struct buffer*) ; 
 unsigned int IA_EMPTY_IF_UNDEF ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char*) ; 
 int /*<<< orphan*/  in6addr_any ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,struct in6_addr*,char*,int) ; 
 scalar_t__ memcmp (struct in6_addr*,int /*<<< orphan*/ *,int) ; 

const char *
print_in6_addr(struct in6_addr a6, unsigned int flags, struct gc_arena *gc)
{
    struct buffer out = alloc_buf_gc(64, gc);
    char tmp_out_buf[64];       /* inet_ntop wants pointer to buffer */

    if (memcmp(&a6, &in6addr_any, sizeof(a6)) != 0
        || !(flags & IA_EMPTY_IF_UNDEF))
    {
        inet_ntop(AF_INET6, &a6, tmp_out_buf, sizeof(tmp_out_buf)-1);
        buf_printf(&out, "%s", tmp_out_buf );
    }
    return BSTR(&out);
}