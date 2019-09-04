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
struct sst_hsw {struct sst_dsp* dsp; } ;
struct sst_dsp {int dummy; } ;

/* Variables and functions */

struct sst_dsp *sst_hsw_get_dsp(struct sst_hsw *hsw)
{
	return hsw->dsp;
}