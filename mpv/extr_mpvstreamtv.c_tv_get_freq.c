#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  priv; TYPE_1__* functions; } ;
typedef  TYPE_2__ tvi_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  TVI_CONTROL_IS_TUNER ; 
 int /*<<< orphan*/  TVI_CONTROL_TRUE ; 
 int /*<<< orphan*/  TVI_CONTROL_TUN_GET_FREQ ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

int tv_get_freq(tvi_handle_t *tvh, unsigned long *freq)
{
    if (tvh->functions->control(tvh->priv, TVI_CONTROL_IS_TUNER, 0) == TVI_CONTROL_TRUE)
    {
        tvh->functions->control(tvh->priv, TVI_CONTROL_TUN_GET_FREQ, freq);
        MP_VERBOSE(tvh, "Current frequency: %lu (%.3f)\n",
            *freq, *freq/16.0);
    }
    return 1;
}