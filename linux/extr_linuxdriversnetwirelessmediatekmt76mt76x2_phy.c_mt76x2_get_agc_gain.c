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
typedef  int /*<<< orphan*/  u8 ;
struct mt76x2_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_BBP_AGC_GAIN ; 
 int /*<<< orphan*/  mt76_get_field (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt76x2_get_agc_gain(struct mt76x2_dev *dev, u8 *dest)
{
	dest[0] = mt76_get_field(dev, MT_BBP(AGC, 8), MT_BBP_AGC_GAIN);
	dest[1] = mt76_get_field(dev, MT_BBP(AGC, 9), MT_BBP_AGC_GAIN);
}