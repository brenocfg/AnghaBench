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
struct wlandevice {struct hfa384x* priv; } ;
struct TYPE_5__ {int scanchannels; struct hfa384x_ch_info_result_sub* result; } ;
struct TYPE_6__ {TYPE_1__ chinforesult; } ;
struct hfa384x_inf_frame {TYPE_2__ info; } ;
struct hfa384x_ch_info_result_sub {int chid; int active; int /*<<< orphan*/  pnl; int /*<<< orphan*/  anl; } ;
struct TYPE_7__ {int scanchannels; struct hfa384x_ch_info_result_sub* result; } ;
struct TYPE_8__ {unsigned int count; int /*<<< orphan*/  done; TYPE_3__ results; } ;
struct hfa384x {TYPE_4__ channel_info; } ;

/* Variables and functions */
 int HFA384x_CHINFORESULT_BSSACTIVE ; 
 unsigned int HFA384x_CHINFORESULT_MAX ; 
 int HFA384x_CHINFORESULT_PCFACTIVE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void prism2sta_inf_chinforesults(struct wlandevice *wlandev,
					struct hfa384x_inf_frame *inf)
{
	struct hfa384x *hw = wlandev->priv;
	unsigned int i, n;

	hw->channel_info.results.scanchannels =
	    inf->info.chinforesult.scanchannels;

	for (i = 0, n = 0; i < HFA384x_CHINFORESULT_MAX; i++) {
		struct hfa384x_ch_info_result_sub *result;
		struct hfa384x_ch_info_result_sub *chinforesult;
		int chan;

		if (!(hw->channel_info.results.scanchannels & (1 << i)))
			continue;

		result = &inf->info.chinforesult.result[n];
		chan = result->chid - 1;

		if (chan < 0 || chan >= HFA384x_CHINFORESULT_MAX)
			continue;

		chinforesult = &hw->channel_info.results.result[chan];
		chinforesult->chid = chan;
		chinforesult->anl = result->anl;
		chinforesult->pnl = result->pnl;
		chinforesult->active = result->active;

		pr_debug("chinfo: channel %d, %s level (avg/peak)=%d/%d dB, pcf %d\n",
			 chan + 1,
			 (chinforesult->active & HFA384x_CHINFORESULT_BSSACTIVE)
				? "signal" : "noise",
			 chinforesult->anl, chinforesult->pnl,
			 (chinforesult->active & HFA384x_CHINFORESULT_PCFACTIVE)
				? 1 : 0);
		n++;
	}
	atomic_set(&hw->channel_info.done, 2);

	hw->channel_info.count = n;
}