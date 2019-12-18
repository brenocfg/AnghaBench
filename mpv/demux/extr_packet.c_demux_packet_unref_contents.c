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
struct demux_packet {scalar_t__ len; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * avpacket; int /*<<< orphan*/  is_cached; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 

void demux_packet_unref_contents(struct demux_packet *dp)
{
    if (dp->avpacket) {
        assert(!dp->is_cached);
        av_packet_unref(dp->avpacket);
        talloc_free(dp->avpacket);
        dp->avpacket = NULL;
        dp->buffer = NULL;
        dp->len = 0;
    }
}