#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t chanlist; size_t channel; struct CHANLIST* chanlist_s; int /*<<< orphan*/  tv_channel_last_real; int /*<<< orphan*/ * tv_channel_current; int /*<<< orphan*/ * tv_channel_last; scalar_t__ tv_channel_list; TYPE_1__* tv_param; } ;
typedef  TYPE_2__ tvi_handle_t ;
typedef  int /*<<< orphan*/  tv_channels_t ;
struct CHANLIST {double freq; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int count; } ;
struct TYPE_8__ {scalar_t__ scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (TYPE_2__*,char*,int /*<<< orphan*/ ,double) ; 
 TYPE_6__* chanlists ; 
 int /*<<< orphan*/  set_norm_and_freq (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv_set_freq_float (TYPE_2__*,double) ; 

int tv_last_channel(tvi_handle_t *tvh) {

        tvh->tv_param->scan=0;
        if (tvh->tv_channel_list) {
                tv_channels_t *tmp;

                tmp = tvh->tv_channel_last;
                tvh->tv_channel_last = tvh->tv_channel_current;
                tvh->tv_channel_current = tmp;

                set_norm_and_freq(tvh, tvh->tv_channel_current);
        } else {
                int i;
                struct CHANLIST cl;

                for (i = 0; i < chanlists[tvh->chanlist].count; i++)
                {
                    cl = tvh->chanlist_s[i];
                    if (!strcasecmp(cl.name, tvh->tv_channel_last_real))
                    {
                        strcpy(tvh->tv_channel_last_real, tvh->chanlist_s[tvh->channel].name);
                        tvh->channel = i;
                        MP_INFO(tvh, "Selected channel: %s (freq: %.3f)\n",
                            cl.name, cl.freq/1000.0);
                        tv_set_freq_float(tvh, cl.freq);
                        break;
                    }
                }
        }
        return 1;
}