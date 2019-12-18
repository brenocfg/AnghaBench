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
struct device {int dummy; } ;

/* Variables and functions */
#define  RT5631_EQ_CTRL 132 
#define  RT5631_INDEX_ADD 131 
#define  RT5631_INDEX_DATA 130 
#define  RT5631_INT_ST_IRQ_CTRL_2 129 
#define  RT5631_RESET 128 

__attribute__((used)) static bool rt5631_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case RT5631_RESET:
	case RT5631_INT_ST_IRQ_CTRL_2:
	case RT5631_INDEX_ADD:
	case RT5631_INDEX_DATA:
	case RT5631_EQ_CTRL:
		return true;
	default:
		return false;
	}
}