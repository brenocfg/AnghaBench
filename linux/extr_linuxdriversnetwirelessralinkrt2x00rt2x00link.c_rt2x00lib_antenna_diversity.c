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
struct link_ant {int flags; } ;
struct TYPE_2__ {int count; struct link_ant ant; } ;
struct rt2x00_dev {TYPE_1__ link; } ;

/* Variables and functions */
 int ANTENNA_MODE_SAMPLE ; 
 int ANTENNA_RX_DIVERSITY ; 
 int ANTENNA_TX_DIVERSITY ; 
 int /*<<< orphan*/  rt2x00lib_antenna_diversity_eval (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00lib_antenna_diversity_sample (struct rt2x00_dev*) ; 

__attribute__((used)) static bool rt2x00lib_antenna_diversity(struct rt2x00_dev *rt2x00dev)
{
	struct link_ant *ant = &rt2x00dev->link.ant;

	/*
	 * Determine if software diversity is enabled for
	 * either the TX or RX antenna (or both).
	 */
	if (!(ant->flags & ANTENNA_RX_DIVERSITY) &&
	    !(ant->flags & ANTENNA_TX_DIVERSITY)) {
		ant->flags = 0;
		return true;
	}

	/*
	 * If we have only sampled the data over the last period
	 * we should now harvest the data. Otherwise just evaluate
	 * the data. The latter should only be performed once
	 * every 2 seconds.
	 */
	if (ant->flags & ANTENNA_MODE_SAMPLE) {
		rt2x00lib_antenna_diversity_sample(rt2x00dev);
		return true;
	} else if (rt2x00dev->link.count & 1) {
		rt2x00lib_antenna_diversity_eval(rt2x00dev);
		return true;
	}

	return false;
}