#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ const u16 ;
struct TYPE_2__ {scalar_t__ fcnt; } ;

/* Variables and functions */
 scalar_t__ CDT3_BD_MASK ; 
 TYPE_1__ g ; 

__attribute__((used)) static inline bool check_bytes_per_frame(u32 bytes_per_frame)
{
	u16 const bd_factor = g.fcnt + 2;
	u16 const max_size = ((u16)CDT3_BD_MASK + 1u) >> bd_factor;

	if (bytes_per_frame <= 0)
		return false; /* too small */

	if (bytes_per_frame > max_size)
		return false; /* too big */

	return true;
}