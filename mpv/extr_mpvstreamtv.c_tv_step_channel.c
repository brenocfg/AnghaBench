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
struct TYPE_8__ {TYPE_6__* tv_channel_current; TYPE_6__* tv_channel_last; TYPE_6__* tv_channel_list; TYPE_1__* tv_param; } ;
typedef  TYPE_2__ tvi_handle_t ;
struct TYPE_9__ {struct TYPE_9__* next; struct TYPE_9__* prev; } ;
struct TYPE_7__ {scalar_t__ scan; } ;

/* Variables and functions */
 int TV_CHANNEL_HIGHER ; 
 int TV_CHANNEL_LOWER ; 
 int /*<<< orphan*/  set_norm_and_freq (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  tv_step_channel_real (TYPE_2__*,int) ; 

int tv_step_channel(tvi_handle_t *tvh, int direction) {
        tvh->tv_param->scan=0;
        if (tvh->tv_channel_list) {
                if (direction == TV_CHANNEL_HIGHER) {
                        tvh->tv_channel_last = tvh->tv_channel_current;
                        if (tvh->tv_channel_current->next)
                                tvh->tv_channel_current = tvh->tv_channel_current->next;
                        else
                                tvh->tv_channel_current = tvh->tv_channel_list;
                        set_norm_and_freq(tvh, tvh->tv_channel_current);
                }
                if (direction == TV_CHANNEL_LOWER) {
                        tvh->tv_channel_last = tvh->tv_channel_current;
                        if (tvh->tv_channel_current->prev)
                                tvh->tv_channel_current = tvh->tv_channel_current->prev;
                        else
                                while (tvh->tv_channel_current->next)
                                        tvh->tv_channel_current = tvh->tv_channel_current->next;
                        set_norm_and_freq(tvh, tvh->tv_channel_current);
                }
        } else tv_step_channel_real(tvh, direction);
        return 1;
}