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
struct priv {int eof_returned; int /*<<< orphan*/  src; } ;
struct mp_frame {int /*<<< orphan*/  type; struct demux_packet* member_1; int /*<<< orphan*/  member_0; } ;
struct mp_filter {int /*<<< orphan*/ * ppins; struct priv* priv; } ;
struct demux_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FRAME_EOF ; 
 int /*<<< orphan*/  MP_FRAME_PACKET ; 
 scalar_t__ demux_read_packet_async (int /*<<< orphan*/ ,struct demux_packet**) ; 
 int /*<<< orphan*/  mp_pin_in_needs_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_in_write (int /*<<< orphan*/ ,struct mp_frame) ; 

__attribute__((used)) static void process(struct mp_filter *f)
{
    struct priv *p = f->priv;

    if (!mp_pin_in_needs_data(f->ppins[0]))
        return;

    struct demux_packet *pkt = NULL;
    if (demux_read_packet_async(p->src, &pkt) == 0)
        return; // wait

    struct mp_frame frame = {MP_FRAME_PACKET, pkt};
    if (pkt) {
        p->eof_returned = false;
    } else {
        frame.type = MP_FRAME_EOF;

        // While the demuxer will repeat EOFs, filters never do that.
        if (p->eof_returned)
            return;
        p->eof_returned = true;
    }

    mp_pin_in_write(f->ppins[0], frame);
}