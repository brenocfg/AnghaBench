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
struct mt76x0_dev {int /*<<< orphan*/  agc_save; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_BBP_AGC_GAIN ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 

void mt76x0_agc_save(struct mt76x0_dev *dev)
{
	/* Only one RX path */
	dev->agc_save = FIELD_GET(MT_BBP_AGC_GAIN, mt76_rr(dev, MT_BBP(AGC, 8)));
}