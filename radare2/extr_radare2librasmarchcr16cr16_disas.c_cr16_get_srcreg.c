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
typedef  int const ut8 ;
typedef  int ut16 ;

/* Variables and functions */

__attribute__((used)) static inline ut8 cr16_get_srcreg(const ut16 instr)
{
	return (instr >> 1) & 0xF;
}