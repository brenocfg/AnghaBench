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
typedef  int u32 ;
struct rb_info {int hw_options; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
rb_hw_option_match(const struct rb_info *info, u32 mask, u32 val)
{
	return (info->hw_options & (val | mask)) == val;
}