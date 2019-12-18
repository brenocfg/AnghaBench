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
typedef  int u32 ;
struct cfg80211_chan_def {int width; int center_freq1; TYPE_1__* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
#define  NL80211_CHAN_WIDTH_160 131 
#define  NL80211_CHAN_WIDTH_40 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static void chandef_primary_freqs(const struct cfg80211_chan_def *c,
				  u32 *pri40, u32 *pri80)
{
	int tmp;

	switch (c->width) {
	case NL80211_CHAN_WIDTH_40:
		*pri40 = c->center_freq1;
		*pri80 = 0;
		break;
	case NL80211_CHAN_WIDTH_80:
	case NL80211_CHAN_WIDTH_80P80:
		*pri80 = c->center_freq1;
		/* n_P20 */
		tmp = (30 + c->chan->center_freq - c->center_freq1)/20;
		/* n_P40 */
		tmp /= 2;
		/* freq_P40 */
		*pri40 = c->center_freq1 - 20 + 40 * tmp;
		break;
	case NL80211_CHAN_WIDTH_160:
		/* n_P20 */
		tmp = (70 + c->chan->center_freq - c->center_freq1)/20;
		/* n_P40 */
		tmp /= 2;
		/* freq_P40 */
		*pri40 = c->center_freq1 - 60 + 40 * tmp;
		/* n_P80 */
		tmp /= 2;
		*pri80 = c->center_freq1 - 40 + 80 * tmp;
		break;
	default:
		WARN_ON_ONCE(1);
	}
}