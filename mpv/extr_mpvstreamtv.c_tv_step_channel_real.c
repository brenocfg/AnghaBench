#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int channel; size_t chanlist; struct CHANLIST* chanlist_s; int /*<<< orphan*/  tv_channel_last_real; TYPE_1__* tv_param; } ;
typedef  TYPE_2__ tvi_handle_t ;
struct CHANLIST {double freq; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int count; } ;
struct TYPE_7__ {scalar_t__ scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (TYPE_2__*,char*,int /*<<< orphan*/ ,double) ; 
 int TV_CHANNEL_HIGHER ; 
 int TV_CHANNEL_LOWER ; 
 TYPE_5__* chanlists ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv_set_freq_float (TYPE_2__*,double) ; 

int tv_step_channel_real(tvi_handle_t *tvh, int direction)
{
    struct CHANLIST cl;

    tvh->tv_param->scan=0;
    if (direction == TV_CHANNEL_LOWER)
    {
        if (tvh->channel-1 >= 0)
        {
            strcpy(tvh->tv_channel_last_real, tvh->chanlist_s[tvh->channel].name);
            cl = tvh->chanlist_s[--tvh->channel];
            MP_INFO(tvh, "Selected channel: %s (freq: %.3f)\n",
                cl.name, cl.freq/1000.0);
            tv_set_freq_float(tvh, cl.freq);
        }
    }

    if (direction == TV_CHANNEL_HIGHER)
    {
        if (tvh->channel+1 < chanlists[tvh->chanlist].count)
        {
            strcpy(tvh->tv_channel_last_real, tvh->chanlist_s[tvh->channel].name);
            cl = tvh->chanlist_s[++tvh->channel];
            MP_INFO(tvh, "Selected channel: %s (freq: %.3f)\n",
                cl.name, cl.freq/1000.0);
            tv_set_freq_float(tvh, cl.freq);
        }
    }
    return 1;
}