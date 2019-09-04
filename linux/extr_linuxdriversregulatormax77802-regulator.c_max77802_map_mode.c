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
 unsigned int MAX77802_OPMODE_NORMAL ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 

__attribute__((used)) static inline unsigned int max77802_map_mode(unsigned int mode)
{
	return mode == MAX77802_OPMODE_NORMAL ?
		REGULATOR_MODE_NORMAL : REGULATOR_MODE_STANDBY;
}