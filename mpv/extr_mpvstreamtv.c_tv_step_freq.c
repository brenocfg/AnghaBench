#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* tv_param; } ;
typedef  TYPE_2__ tvi_handle_t ;
struct TYPE_6__ {scalar_t__ scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  tv_get_freq (TYPE_2__*,unsigned long*) ; 
 int tv_set_freq (TYPE_2__*,unsigned long) ; 

int tv_step_freq(tvi_handle_t* tvh, float step_interval){
    unsigned long frequency = 0;

    tvh->tv_param->scan=0;
    tv_get_freq(tvh,&frequency);
    frequency+=step_interval;
    return tv_set_freq(tvh,frequency);
}