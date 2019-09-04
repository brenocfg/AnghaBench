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
 int /*<<< orphan*/  W1_DS2781_RECALL_DATA ; 
 int w1_ds2781_eeprom_cmd (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ds2781_recall_eeprom(struct device *dev, int addr)
{
	return w1_ds2781_eeprom_cmd(dev, addr, W1_DS2781_RECALL_DATA);
}