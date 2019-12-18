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
struct frame {int dummy; } ;
struct buffer {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUF_SIZE (struct frame const*) ; 
 int /*<<< orphan*/  FRAME_HEADROOM_ADJ (struct frame const*,unsigned int const) ; 
 int /*<<< orphan*/  MAX_RW_SIZE_LINK (struct frame const*) ; 
 int /*<<< orphan*/  MAX_RW_SIZE_TUN (struct frame const*) ; 
 struct buffer alloc_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_init (struct buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_safe (struct buffer*,int /*<<< orphan*/ ) ; 

void
alloc_buf_sock_tun(struct buffer *buf,
                   const struct frame *frame,
                   const bool tuntap_buffer,
                   const unsigned int align_mask)
{
    /* allocate buffer for overlapped I/O */
    *buf = alloc_buf(BUF_SIZE(frame));
    ASSERT(buf_init(buf, FRAME_HEADROOM_ADJ(frame, align_mask)));
    buf->len = tuntap_buffer ? MAX_RW_SIZE_TUN(frame) : MAX_RW_SIZE_LINK(frame);
    ASSERT(buf_safe(buf, 0));
}