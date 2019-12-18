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
struct encoder_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  obs_encoder_packet_create_instance (struct encoder_packet*,struct encoder_packet const*) ; 

void obs_duplicate_encoder_packet(struct encoder_packet *dst,
				  const struct encoder_packet *src)
{
	obs_encoder_packet_create_instance(dst, src);
}