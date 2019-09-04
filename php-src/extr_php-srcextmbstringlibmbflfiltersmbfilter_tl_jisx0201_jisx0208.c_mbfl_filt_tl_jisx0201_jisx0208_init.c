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
typedef  int /*<<< orphan*/  mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_filt_conv_common_ctor (int /*<<< orphan*/ *) ; 

void
mbfl_filt_tl_jisx0201_jisx0208_init(mbfl_convert_filter *filt)
{
	mbfl_filt_conv_common_ctor(filt);
}