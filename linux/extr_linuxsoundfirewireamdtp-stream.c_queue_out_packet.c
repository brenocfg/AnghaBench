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
struct amdtp_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUT_PACKET_HEADER_SIZE ; 
 int queue_packet (struct amdtp_stream*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int queue_out_packet(struct amdtp_stream *s,
				   unsigned int payload_length)
{
	return queue_packet(s, OUT_PACKET_HEADER_SIZE, payload_length);
}