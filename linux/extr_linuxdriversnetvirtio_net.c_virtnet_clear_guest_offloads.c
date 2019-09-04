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
typedef  int /*<<< orphan*/  u64 ;
struct virtnet_info {int /*<<< orphan*/  guest_offloads; } ;

/* Variables and functions */
 int virtnet_set_guest_offloads (struct virtnet_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtnet_clear_guest_offloads(struct virtnet_info *vi)
{
	u64 offloads = 0;

	if (!vi->guest_offloads)
		return 0;

	return virtnet_set_guest_offloads(vi, offloads);
}