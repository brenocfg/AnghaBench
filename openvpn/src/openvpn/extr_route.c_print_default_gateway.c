#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  netbits_ipv6; int /*<<< orphan*/  addr_ipv6; } ;
struct route_ipv6_gateway_info {int flags; int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  iface; int /*<<< orphan*/  adapter_index; TYPE_2__ gateway; } ;
struct TYPE_3__ {int /*<<< orphan*/  netmask; int /*<<< orphan*/  addr; } ;
struct route_gateway_info {int flags; int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  iface; int /*<<< orphan*/  adapter_index; TYPE_1__ gateway; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR (struct buffer*) ; 
 int RGI_ADDR_DEFINED ; 
 int RGI_HWADDR_DEFINED ; 
 int RGI_IFACE_DEFINED ; 
 int RGI_NETMASK_DEFINED ; 
 int RGI_ON_LINK ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,...) ; 
 int /*<<< orphan*/  format_hex_ex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,char*,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int const,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_in6_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  print_in_addr_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gc_arena*) ; 

void
print_default_gateway(const int msglevel,
                      const struct route_gateway_info *rgi,
                      const struct route_ipv6_gateway_info *rgi6)
{
    struct gc_arena gc = gc_new();
    if (rgi && (rgi->flags & RGI_ADDR_DEFINED))
    {
        struct buffer out = alloc_buf_gc(256, &gc);
        buf_printf(&out, "ROUTE_GATEWAY");
        if (rgi->flags & RGI_ON_LINK)
        {
            buf_printf(&out, " ON_LINK");
        }
        else
        {
            buf_printf(&out, " %s", print_in_addr_t(rgi->gateway.addr, 0, &gc));
        }
        if (rgi->flags & RGI_NETMASK_DEFINED)
        {
            buf_printf(&out, "/%s", print_in_addr_t(rgi->gateway.netmask, 0, &gc));
        }
#ifdef _WIN32
        if (rgi->flags & RGI_IFACE_DEFINED)
        {
            buf_printf(&out, " I=%lu", rgi->adapter_index);
        }
#else
        if (rgi->flags & RGI_IFACE_DEFINED)
        {
            buf_printf(&out, " IFACE=%s", rgi->iface);
        }
#endif
        if (rgi->flags & RGI_HWADDR_DEFINED)
        {
            buf_printf(&out, " HWADDR=%s", format_hex_ex(rgi->hwaddr, 6, 0, 1, ":", &gc));
        }
        msg(msglevel, "%s", BSTR(&out));
    }

    if (rgi6 && (rgi6->flags & RGI_ADDR_DEFINED))
    {
        struct buffer out = alloc_buf_gc(256, &gc);
        buf_printf(&out, "ROUTE6_GATEWAY");
        buf_printf(&out, " %s", print_in6_addr(rgi6->gateway.addr_ipv6, 0, &gc));
        if (rgi6->flags & RGI_ON_LINK)
        {
            buf_printf(&out, " ON_LINK");
        }
        if (rgi6->flags & RGI_NETMASK_DEFINED)
        {
            buf_printf(&out, "/%d", rgi6->gateway.netbits_ipv6);
        }
#ifdef _WIN32
        if (rgi6->flags & RGI_IFACE_DEFINED)
        {
            buf_printf(&out, " I=%lu", rgi6->adapter_index);
        }
#else
        if (rgi6->flags & RGI_IFACE_DEFINED)
        {
            buf_printf(&out, " IFACE=%s", rgi6->iface);
        }
#endif
        if (rgi6->flags & RGI_HWADDR_DEFINED)
        {
            buf_printf(&out, " HWADDR=%s", format_hex_ex(rgi6->hwaddr, 6, 0, 1, ":", &gc));
        }
        msg(msglevel, "%s", BSTR(&out));
    }
    gc_free(&gc);
}