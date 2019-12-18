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
struct frame {int /*<<< orphan*/  link_mtu; scalar_t__ link_mtu_dynamic; int /*<<< orphan*/  extra_link; } ;
typedef  int /*<<< orphan*/  packet_id_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CONTROL_SEND_ACK_MAX ; 
 scalar_t__ SID_SIZE ; 
 scalar_t__ TUN_LINK_DELTA (struct frame*) ; 
 int /*<<< orphan*/  frame_add_to_extra_frame (struct frame*,scalar_t__) ; 
 scalar_t__ min_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reliable_ack_adjust_frame_parameters (struct frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_adjust_frame_parameters (struct frame*) ; 

__attribute__((used)) static void
tls_init_control_channel_frame_parameters(const struct frame *data_channel_frame,
                                          struct frame *frame)
{
    /*
     * frame->extra_frame is already initialized with tls_auth buffer requirements,
     * if --tls-auth is enabled.
     */

    /* inherit link MTU and extra_link from data channel */
    frame->link_mtu = data_channel_frame->link_mtu;
    frame->extra_link = data_channel_frame->extra_link;

    /* set extra_frame */
    tls_adjust_frame_parameters(frame);
    reliable_ack_adjust_frame_parameters(frame, CONTROL_SEND_ACK_MAX);
    frame_add_to_extra_frame(frame, SID_SIZE + sizeof(packet_id_type));

    /* set dynamic link MTU to cap control channel packets at 1250 bytes */
    ASSERT(TUN_LINK_DELTA(frame) < min_int(frame->link_mtu, 1250));
    frame->link_mtu_dynamic = min_int(frame->link_mtu, 1250) - TUN_LINK_DELTA(frame);
}