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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 wsm_queue_id_to_wsm(u8 queue_id)
{
	static const u8 queue_mapping[] = {
		3, 2, 0, 1
	};
	return queue_mapping[queue_id];
}