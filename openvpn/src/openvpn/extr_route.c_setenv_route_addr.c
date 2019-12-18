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
struct env_set {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR (struct buffer*) ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char const*,...) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  print_in_addr_t (int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setenv_route_addr(struct env_set *es, const char *key, const in_addr_t addr, int i)
{
    struct gc_arena gc = gc_new();
    struct buffer name = alloc_buf_gc(256, &gc);
    if (i >= 0)
    {
        buf_printf(&name, "route_%s_%d", key, i);
    }
    else
    {
        buf_printf(&name, "route_%s", key);
    }
    setenv_str(es, BSTR(&name), print_in_addr_t(addr, 0, &gc));
    gc_free(&gc);
}