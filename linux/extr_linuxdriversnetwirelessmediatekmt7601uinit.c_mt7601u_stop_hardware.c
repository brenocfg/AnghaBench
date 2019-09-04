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
 int /*<<< orphan*/  mt7601u_chip_onoff (struct mt7601u_dev*,int,int) ; 

__attribute__((used)) static void mt7601u_stop_hardware(struct mt7601u_dev *dev)
{
	mt7601u_chip_onoff(dev, false, false);
}