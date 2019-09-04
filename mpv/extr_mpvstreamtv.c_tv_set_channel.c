#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_6__* tv_channel_current; TYPE_6__* tv_channel_list; TYPE_6__* tv_channel_last; TYPE_1__* tv_param; } ;
typedef  TYPE_2__ tvi_handle_t ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
struct TYPE_7__ {scalar_t__ scan; } ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  set_norm_and_freq (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  tv_set_channel_real (TYPE_2__*,char*) ; 

int tv_set_channel(tvi_handle_t *tvh, char *channel) {
        int i, channel_int;

        tvh->tv_param->scan=0;
        if (tvh->tv_channel_list) {
                tvh->tv_channel_last = tvh->tv_channel_current;
                channel_int = atoi(channel);
                tvh->tv_channel_current = tvh->tv_channel_list;
                for (i = 1; i < channel_int; i++)
                        if (tvh->tv_channel_current->next)
                                tvh->tv_channel_current = tvh->tv_channel_current->next;
                set_norm_and_freq(tvh, tvh->tv_channel_current);
        } else tv_set_channel_real(tvh, channel);
        return 1;
}