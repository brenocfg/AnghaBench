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
struct demux_packet {size_t len; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void demux_packet_shorten(struct demux_packet *dp, size_t len)
{
    assert(len <= dp->len);
    if (dp->len) {
        dp->len = len;
        memset(dp->buffer + dp->len, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    }
}