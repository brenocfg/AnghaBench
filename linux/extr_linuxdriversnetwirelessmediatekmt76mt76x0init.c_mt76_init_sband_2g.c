#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  sband; } ;
struct TYPE_12__ {TYPE_5__ sband_2g; TYPE_4__* hw; } ;
struct mt76x0_dev {TYPE_6__ mt76; TYPE_2__* ee; } ;
struct TYPE_10__ {TYPE_3__* wiphy; } ;
struct TYPE_9__ {int /*<<< orphan*/ ** bands; } ;
struct TYPE_7__ {int start; int num; } ;
struct TYPE_8__ {TYPE_1__ reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mt76_channels_2ghz ; 
 int mt76_init_sband (struct mt76x0_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rates ; 

__attribute__((used)) static int
mt76_init_sband_2g(struct mt76x0_dev *dev)
{
	dev->mt76.hw->wiphy->bands[NL80211_BAND_2GHZ] = &dev->mt76.sband_2g.sband;

	WARN_ON(dev->ee->reg.start - 1 + dev->ee->reg.num >
		ARRAY_SIZE(mt76_channels_2ghz));


	return mt76_init_sband(dev, &dev->mt76.sband_2g.sband,
			       mt76_channels_2ghz, ARRAY_SIZE(mt76_channels_2ghz),
			       mt76_rates, ARRAY_SIZE(mt76_rates));
}