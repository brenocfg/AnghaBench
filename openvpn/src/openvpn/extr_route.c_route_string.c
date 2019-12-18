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
struct route_ipv4 {int flags; int /*<<< orphan*/  metric; int /*<<< orphan*/  gateway; int /*<<< orphan*/  netmask; int /*<<< orphan*/  network; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 char const* BSTR (struct buffer*) ; 
 int RT_METRIC_DEFINED ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  print_in_addr_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gc_arena*) ; 

__attribute__((used)) static const char *
route_string(const struct route_ipv4 *r, struct gc_arena *gc)
{
    struct buffer out = alloc_buf_gc(256, gc);
    buf_printf(&out, "ROUTE network %s netmask %s gateway %s",
               print_in_addr_t(r->network, 0, gc),
               print_in_addr_t(r->netmask, 0, gc),
               print_in_addr_t(r->gateway, 0, gc)
               );
    if (r->flags & RT_METRIC_DEFINED)
    {
        buf_printf(&out, " metric %d", r->metric);
    }
    return BSTR(&out);
}