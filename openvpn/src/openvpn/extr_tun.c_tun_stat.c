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
struct tuntap {unsigned int rwflags_debug; int /*<<< orphan*/  writes; int /*<<< orphan*/  reads; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 char const* BSTR (struct buffer*) ; 
 unsigned int EVENT_READ ; 
 unsigned int EVENT_WRITE ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,...) ; 
 int /*<<< orphan*/  overlapped_io_state_ascii (int /*<<< orphan*/ *) ; 

const char *
tun_stat(const struct tuntap *tt, unsigned int rwflags, struct gc_arena *gc)
{
    struct buffer out = alloc_buf_gc(64, gc);
    if (tt)
    {
        if (rwflags & EVENT_READ)
        {
            buf_printf(&out, "T%s",
                       (tt->rwflags_debug & EVENT_READ) ? "R" : "r");
#ifdef _WIN32
            buf_printf(&out, "%s",
                       overlapped_io_state_ascii(&tt->reads));
#endif
        }
        if (rwflags & EVENT_WRITE)
        {
            buf_printf(&out, "T%s",
                       (tt->rwflags_debug & EVENT_WRITE) ? "W" : "w");
#ifdef _WIN32
            buf_printf(&out, "%s",
                       overlapped_io_state_ascii(&tt->writes));
#endif
        }
    }
    else
    {
        buf_printf(&out, "T?");
    }
    return BSTR(&out);
}