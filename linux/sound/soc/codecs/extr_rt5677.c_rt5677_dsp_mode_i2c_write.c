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
struct rt5677_priv {int dummy; } ;

/* Variables and functions */
 int rt5677_dsp_mode_i2c_write_addr (struct rt5677_priv*,int,unsigned int,int) ; 

__attribute__((used)) static int rt5677_dsp_mode_i2c_write(struct rt5677_priv *rt5677,
		unsigned int reg, unsigned int value)
{
	return rt5677_dsp_mode_i2c_write_addr(rt5677, 0x18020000 + reg * 2,
		value, 0x0001);
}