#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  priv; TYPE_1__* functions; } ;
typedef  TYPE_2__ tvi_handle_t ;
struct TYPE_4__ {scalar_t__ (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TVI_CONTROL_IS_TUNER ; 
 scalar_t__ TVI_CONTROL_TRUE ; 
 int /*<<< orphan*/  TVI_CONTROL_TUN_GET_SIGNAL ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int tv_get_signal(tvi_handle_t *tvh)
{
    int signal=0;
    if (tvh->functions->control(tvh->priv, TVI_CONTROL_IS_TUNER, 0) != TVI_CONTROL_TRUE ||
        tvh->functions->control(tvh->priv, TVI_CONTROL_TUN_GET_SIGNAL, &signal)!=TVI_CONTROL_TRUE)
        return 0;

    return signal;
}