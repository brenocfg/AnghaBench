#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tvi_handle_t ;
struct TYPE_3__ {double freq; int /*<<< orphan*/  norm; int /*<<< orphan*/  name; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ tv_channels_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  tv_set_freq_float (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  tv_set_norm_i (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_norm_and_freq(tvi_handle_t *tvh, tv_channels_t *chan)
{
    MP_INFO(tvh, "Selected channel: %s - %s (freq: %.3f)\n",
           chan->number, chan->name, chan->freq/1000.0);
    tv_set_norm_i(tvh, chan->norm);
    tv_set_freq_float(tvh, chan->freq);
}