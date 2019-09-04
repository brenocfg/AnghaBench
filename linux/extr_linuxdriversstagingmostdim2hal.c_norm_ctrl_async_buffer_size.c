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
typedef  scalar_t__ const u16 ;

/* Variables and functions */
 scalar_t__ ADT1_CTRL_ASYNC_BD_MASK ; 

__attribute__((used)) static inline u16 norm_ctrl_async_buffer_size(u16 buf_size)
{
	u16 const max_size = (u16)ADT1_CTRL_ASYNC_BD_MASK + 1u;

	if (buf_size > max_size)
		return max_size;

	return buf_size;
}