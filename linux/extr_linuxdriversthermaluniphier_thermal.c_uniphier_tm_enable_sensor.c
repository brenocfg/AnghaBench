#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_tm_dev {TYPE_1__* data; scalar_t__* alert_en; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {scalar_t__ block_base; scalar_t__ map_base; } ;

/* Variables and functions */
 int ALERT_CH_NUM ; 
 scalar_t__ PMALERTINTCTL ; 
 int /*<<< orphan*/  PMALERTINTCTL_EN (int) ; 
 int /*<<< orphan*/  PMALERTINTCTL_MASK ; 
 scalar_t__ PVTCTLEN ; 
 int /*<<< orphan*/  PVTCTLEN_EN ; 
 int /*<<< orphan*/  regmap_write_bits (struct regmap*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void uniphier_tm_enable_sensor(struct uniphier_tm_dev *tdev)
{
	struct regmap *map = tdev->regmap;
	int i;
	u32 bits = 0;

	for (i = 0; i < ALERT_CH_NUM; i++)
		if (tdev->alert_en[i])
			bits |= PMALERTINTCTL_EN(i);

	/* enable alert interrupt */
	regmap_write_bits(map, tdev->data->map_base + PMALERTINTCTL,
			  PMALERTINTCTL_MASK, bits);

	/* start PVT */
	regmap_write_bits(map, tdev->data->block_base + PVTCTLEN,
			  PVTCTLEN_EN, PVTCTLEN_EN);

	usleep_range(700, 1500);	/* The spec note says at least 700us */
}