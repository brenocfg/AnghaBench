#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sband; } ;
struct TYPE_8__ {TYPE_3__ sband_5g; TYPE_2__* hw; } ;
struct mt76x0_dev {TYPE_4__ mt76; } ;
struct TYPE_6__ {TYPE_1__* wiphy; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** bands; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (scalar_t__) ; 
 size_t NL80211_BAND_5GHZ ; 
 scalar_t__ mt76_channels_5ghz ; 
 int mt76_init_sband (struct mt76x0_dev*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mt76_rates ; 

__attribute__((used)) static int
mt76_init_sband_5g(struct mt76x0_dev *dev)
{
	dev->mt76.hw->wiphy->bands[NL80211_BAND_5GHZ] = &dev->mt76.sband_5g.sband;

	return mt76_init_sband(dev, &dev->mt76.sband_5g.sband,
			       mt76_channels_5ghz, ARRAY_SIZE(mt76_channels_5ghz),
			       mt76_rates + 4, ARRAY_SIZE(mt76_rates) - 4);
}