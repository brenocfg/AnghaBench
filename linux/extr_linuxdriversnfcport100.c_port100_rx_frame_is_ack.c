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
struct port100_ack_frame {scalar_t__ start_frame; scalar_t__ ack_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT100_FRAME_ACK ; 
 int /*<<< orphan*/  PORT100_FRAME_SOF ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool port100_rx_frame_is_ack(struct port100_ack_frame *frame)
{
	return (frame->start_frame == cpu_to_be16(PORT100_FRAME_SOF) &&
		frame->ack_frame == cpu_to_be16(PORT100_FRAME_ACK));
}