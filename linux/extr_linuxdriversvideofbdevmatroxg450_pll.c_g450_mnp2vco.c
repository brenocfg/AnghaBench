#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int ref_freq; } ;
struct TYPE_4__ {TYPE_1__ pll; } ;
struct matrox_fb_info {TYPE_2__ features; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int g450_mnp2vco(const struct matrox_fb_info *minfo,
				 unsigned int mnp)
{
	unsigned int m, n;

	m = ((mnp >> 16) & 0x0FF) + 1;
	n = ((mnp >>  7) & 0x1FE) + 4;
	return (minfo->features.pll.ref_freq * n + (m >> 1)) / m;
}