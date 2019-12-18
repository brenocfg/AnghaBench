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
struct frame {int /*<<< orphan*/  align_adjust; int /*<<< orphan*/  align_flags; int /*<<< orphan*/  extra_link; int /*<<< orphan*/  extra_tun; int /*<<< orphan*/  extra_buffer; int /*<<< orphan*/  extra_frame; int /*<<< orphan*/  link_mtu_dynamic; int /*<<< orphan*/  link_mtu; } ;
struct buffer {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,...) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int,char*,int /*<<< orphan*/ ) ; 

void
frame_print(const struct frame *frame,
            int level,
            const char *prefix)
{
    struct gc_arena gc = gc_new();
    struct buffer out = alloc_buf_gc(256, &gc);
    if (prefix)
    {
        buf_printf(&out, "%s ", prefix);
    }
    buf_printf(&out, "[");
    buf_printf(&out, " L:%d", frame->link_mtu);
    buf_printf(&out, " D:%d", frame->link_mtu_dynamic);
    buf_printf(&out, " EF:%d", frame->extra_frame);
    buf_printf(&out, " EB:%d", frame->extra_buffer);
    buf_printf(&out, " ET:%d", frame->extra_tun);
    buf_printf(&out, " EL:%d", frame->extra_link);
    if (frame->align_flags && frame->align_adjust)
    {
        buf_printf(&out, " AF:%u/%d", frame->align_flags, frame->align_adjust);
    }
    buf_printf(&out, " ]");

    msg(level, "%s", out.data);
    gc_free(&gc);
}