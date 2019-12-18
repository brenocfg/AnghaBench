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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_iface_combination {int /*<<< orphan*/  num_different_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ieee80211_iter_max_chans(const struct ieee80211_iface_combination *c,
			 void *data)
{
	u32 *max_num_different_channels = data;

	*max_num_different_channels = max(*max_num_different_channels,
					  c->num_different_channels);
}