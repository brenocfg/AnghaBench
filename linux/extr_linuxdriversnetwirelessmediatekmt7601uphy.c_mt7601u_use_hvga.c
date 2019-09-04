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
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int mt7601u_current_tx_power (struct mt7601u_dev*) ; 

__attribute__((used)) static bool mt7601u_use_hvga(struct mt7601u_dev *dev)
{
	return !(mt7601u_current_tx_power(dev) > 20);
}