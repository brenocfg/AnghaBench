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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__* coefficient_sizes ; 

__attribute__((used)) static u16
snd_nm256_get_start_offset(int which)
{
	u16 offset = 0;
	while (which-- > 0)
		offset += coefficient_sizes[which];
	return offset;
}