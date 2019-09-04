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
struct usbip_header_basic {void* ep; void* direction; void* devid; void* seqnum; void* command; } ;

/* Variables and functions */
 void* be32_to_cpu (void*) ; 
 void* cpu_to_be32 (void*) ; 

__attribute__((used)) static void correct_endian_basic(struct usbip_header_basic *base, int send)
{
	if (send) {
		base->command	= cpu_to_be32(base->command);
		base->seqnum	= cpu_to_be32(base->seqnum);
		base->devid	= cpu_to_be32(base->devid);
		base->direction	= cpu_to_be32(base->direction);
		base->ep	= cpu_to_be32(base->ep);
	} else {
		base->command	= be32_to_cpu(base->command);
		base->seqnum	= be32_to_cpu(base->seqnum);
		base->devid	= be32_to_cpu(base->devid);
		base->direction	= be32_to_cpu(base->direction);
		base->ep	= be32_to_cpu(base->ep);
	}
}