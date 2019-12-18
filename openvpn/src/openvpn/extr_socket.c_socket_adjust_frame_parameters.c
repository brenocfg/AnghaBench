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
typedef  int /*<<< orphan*/  packet_size_type ;

/* Variables and functions */
 int /*<<< orphan*/  frame_add_to_extra_frame (struct frame*,int) ; 
 scalar_t__ link_socket_proto_connection_oriented (int) ; 

void
socket_adjust_frame_parameters(struct frame *frame, int proto)
{
    if (link_socket_proto_connection_oriented(proto))
    {
        frame_add_to_extra_frame(frame, sizeof(packet_size_type));
    }
}