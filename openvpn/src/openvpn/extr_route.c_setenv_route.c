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
struct env_set {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR (struct buffer*) ; 
 int RT_DEFINED ; 
 int RT_METRIC_DEFINED ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,int) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  setenv_int (struct env_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv_route_addr (struct env_set*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setenv_route(struct env_set *es, const struct route_ipv4 *r, int i)
{
    struct gc_arena gc = gc_new();
    if (r->flags & RT_DEFINED)
    {
        setenv_route_addr(es, "network", r->network, i);
        setenv_route_addr(es, "netmask", r->netmask, i);
        setenv_route_addr(es, "gateway", r->gateway, i);

        if (r->flags & RT_METRIC_DEFINED)
        {
            struct buffer name = alloc_buf_gc(256, &gc);
            buf_printf(&name, "route_metric_%d", i);
            setenv_int(es, BSTR(&name), r->metric);
        }
    }
    gc_free(&gc);
}