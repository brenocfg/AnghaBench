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
typedef  enum sub_frame_type { ____Placeholder_sub_frame_type } sub_frame_type ;

/* Variables and functions */

__attribute__((used)) static inline enum sub_frame_type get_sub_type(u8 *header)
{
	return ((enum sub_frame_type)(header[0] & 0xFC));
}