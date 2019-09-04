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
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mt7601u_rf_set (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_rf_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mt7601u_vco_cal(struct mt7601u_dev *dev)
{
	mt7601u_rf_wr(dev, 0, 4, 0x0a);
	mt7601u_rf_wr(dev, 0, 5, 0x20);
	mt7601u_rf_set(dev, 0, 4, BIT(7));
	msleep(2);
}