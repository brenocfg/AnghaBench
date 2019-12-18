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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,void*,unsigned char) ; 

__attribute__((used)) static void
add_security_buffer(int sb_offset, void *data, int length,
                    unsigned char *msg_buf, int *msg_bufpos)
{
    /* Adds security buffer data to a message and sets security buffer's
     * offset and length */
    msg_buf[sb_offset] = (unsigned char)length;
    msg_buf[sb_offset + 2] = msg_buf[sb_offset];
    msg_buf[sb_offset + 4] = (unsigned char)(*msg_bufpos & 0xff);
    msg_buf[sb_offset + 5] = (unsigned char)((*msg_bufpos >> 8) & 0xff);
    memcpy(&msg_buf[*msg_bufpos], data, msg_buf[sb_offset]);
    *msg_bufpos += length;
}