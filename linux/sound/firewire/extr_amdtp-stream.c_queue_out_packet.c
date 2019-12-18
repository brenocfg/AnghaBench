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
struct fw_iso_packet {int skip; scalar_t__ header_length; scalar_t__ payload_length; } ;
struct amdtp_stream {int dummy; } ;

/* Variables and functions */
 int queue_packet (struct amdtp_stream*,struct fw_iso_packet*) ; 

__attribute__((used)) static inline int queue_out_packet(struct amdtp_stream *s,
				   struct fw_iso_packet *params)
{
	params->skip =
		!!(params->header_length == 0 && params->payload_length == 0);
	return queue_packet(s, params);
}