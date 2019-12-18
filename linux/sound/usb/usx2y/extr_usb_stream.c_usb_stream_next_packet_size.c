#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_stream_kernel {int out_phase_peeked; int out_phase; int freqn; struct usb_stream* s; } ;
struct TYPE_2__ {int frame_size; } ;
struct usb_stream {TYPE_1__ cfg; } ;

/* Variables and functions */

__attribute__((used)) static unsigned usb_stream_next_packet_size(struct usb_stream_kernel *sk)
{
	struct usb_stream *s = sk->s;
	sk->out_phase_peeked = (sk->out_phase & 0xffff) + sk->freqn;
	return (sk->out_phase_peeked >> 16) * s->cfg.frame_size;
}