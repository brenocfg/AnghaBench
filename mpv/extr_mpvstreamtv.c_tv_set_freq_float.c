#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tvi_handle_t ;

/* Variables and functions */
 int tv_set_freq (int /*<<< orphan*/ *,float) ; 

__attribute__((used)) static int tv_set_freq_float(tvi_handle_t *tvh, float freq)
{
    return tv_set_freq(tvh, freq/1000.0*16);
}