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
struct mtk_base_afe {int dummy; } ;

/* Variables and functions */
 int MT8183_APLL1 ; 

int mt8183_get_apll_rate(struct mtk_base_afe *afe, int apll)
{
	return (apll == MT8183_APLL1) ? 180633600 : 196608000;
}