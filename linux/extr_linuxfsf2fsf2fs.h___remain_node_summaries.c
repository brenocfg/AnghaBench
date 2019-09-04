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

/* Variables and functions */
 int CP_FASTBOOT ; 
 int CP_UMOUNT ; 

__attribute__((used)) static inline bool __remain_node_summaries(int reason)
{
	return (reason & (CP_UMOUNT | CP_FASTBOOT));
}