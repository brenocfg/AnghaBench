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
struct buffer {int dummy; } ;

/* Variables and functions */
 char const* BSTR (struct buffer*) ; 
 struct buffer alloc_buf_gc (scalar_t__,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char const*,...) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static const char *
setenv_format_indexed_name(const char *name, const int i, struct gc_arena *gc)
{
    struct buffer out = alloc_buf_gc(strlen(name) + 16, gc);
    if (i >= 0)
    {
        buf_printf(&out, "%s_%d", name, i);
    }
    else
    {
        buf_printf(&out, "%s", name);
    }
    return BSTR(&out);
}