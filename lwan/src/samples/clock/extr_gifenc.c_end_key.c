#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int offset; int* buffer; int partial; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ ge_GIF ;

/* Variables and functions */
 int /*<<< orphan*/  lwan_strbuf_append_char (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  lwan_strbuf_append_str (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void end_key(ge_GIF *gif)
{
    int byte_offset;

    byte_offset = gif->offset / 8;
    if (gif->offset % 8)
        gif->buffer[byte_offset++] = gif->partial & 0xFF;

    lwan_strbuf_append_char(gif->buf, byte_offset);
    lwan_strbuf_append_str(gif->buf, gif->buffer, byte_offset);
    lwan_strbuf_append_char(gif->buf, '\0');

    gif->offset = gif->partial = 0;
}