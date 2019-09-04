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
struct mp_filter {int dummy; } ;
struct demux_packet {int dummy; } ;

/* Variables and functions */
 int do_send_packet (struct mp_filter*,struct demux_packet*) ; 
 int /*<<< orphan*/  send_queued (struct mp_filter*) ; 

__attribute__((used)) static bool send_packet(struct mp_filter *vd, struct demux_packet *pkt)
{
    if (!send_queued(vd))
        return false;

    return do_send_packet(vd, pkt);
}