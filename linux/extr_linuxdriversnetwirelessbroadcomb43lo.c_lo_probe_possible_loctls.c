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
typedef  scalar_t__ u16 ;
struct b43_phy {struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_g {int /*<<< orphan*/  trsw_rx_gain; int /*<<< orphan*/  pga_gain; int /*<<< orphan*/  lna_gain; } ;
struct b43_loctl {int i; int q; } ;
struct b43_lo_g_statemachine {int current_state; int state_val_multiplier; scalar_t__ lowest_feedth; int nr_measured; } ;
typedef  int /*<<< orphan*/  prev_loctl ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  b43_lo_write (struct b43_wldev*,struct b43_loctl*) ; 
 int /*<<< orphan*/  has_loopback_gain (struct b43_phy*) ; 
 scalar_t__ lo_measure_feedthrough (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct b43_loctl*,struct b43_loctl*,int) ; 

__attribute__((used)) static int lo_probe_possible_loctls(struct b43_wldev *dev,
				    struct b43_loctl *probe_loctl,
				    struct b43_lo_g_statemachine *d)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	struct b43_loctl test_loctl;
	struct b43_loctl orig_loctl;
	struct b43_loctl prev_loctl = {
		.i = -100,
		.q = -100,
	};
	int i;
	int begin, end;
	int found_lower = 0;
	u16 feedth;

	static const struct b43_loctl modifiers[] = {
		{.i = 1,.q = 1,},
		{.i = 1,.q = 0,},
		{.i = 1,.q = -1,},
		{.i = 0,.q = -1,},
		{.i = -1,.q = -1,},
		{.i = -1,.q = 0,},
		{.i = -1,.q = 1,},
		{.i = 0,.q = 1,},
	};

	if (d->current_state == 0) {
		begin = 1;
		end = 8;
	} else if (d->current_state % 2 == 0) {
		begin = d->current_state - 1;
		end = d->current_state + 1;
	} else {
		begin = d->current_state - 2;
		end = d->current_state + 2;
	}
	if (begin < 1)
		begin += 8;
	if (end > 8)
		end -= 8;

	memcpy(&orig_loctl, probe_loctl, sizeof(struct b43_loctl));
	i = begin;
	d->current_state = i;
	while (1) {
		B43_WARN_ON(!(i >= 1 && i <= 8));
		memcpy(&test_loctl, &orig_loctl, sizeof(struct b43_loctl));
		test_loctl.i += modifiers[i - 1].i * d->state_val_multiplier;
		test_loctl.q += modifiers[i - 1].q * d->state_val_multiplier;
		if ((test_loctl.i != prev_loctl.i ||
		     test_loctl.q != prev_loctl.q) &&
		    (abs(test_loctl.i) <= 16 && abs(test_loctl.q) <= 16)) {
			b43_lo_write(dev, &test_loctl);
			feedth = lo_measure_feedthrough(dev, gphy->lna_gain,
							gphy->pga_gain,
							gphy->trsw_rx_gain);
			if (feedth < d->lowest_feedth) {
				memcpy(probe_loctl, &test_loctl,
				       sizeof(struct b43_loctl));
				found_lower = 1;
				d->lowest_feedth = feedth;
				if ((d->nr_measured < 2) &&
				    !has_loopback_gain(phy))
					break;
			}
		}
		memcpy(&prev_loctl, &test_loctl, sizeof(prev_loctl));
		if (i == end)
			break;
		if (i == 8)
			i = 1;
		else
			i++;
		d->current_state = i;
	}

	return found_lower;
}