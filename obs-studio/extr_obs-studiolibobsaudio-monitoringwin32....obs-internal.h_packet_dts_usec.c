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
struct encoder_packet {int dts; int timebase_den; } ;
typedef  int int64_t ;

/* Variables and functions */
 int MICROSECOND_DEN ; 

__attribute__((used)) static inline int64_t packet_dts_usec(struct encoder_packet *packet)
{
	return packet->dts * MICROSECOND_DEN / packet->timebase_den;
}