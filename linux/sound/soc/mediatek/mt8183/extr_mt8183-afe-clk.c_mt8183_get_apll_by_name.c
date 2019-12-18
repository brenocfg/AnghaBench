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
 int /*<<< orphan*/  APLL1_W_NAME ; 
 int MT8183_APLL1 ; 
 int MT8183_APLL2 ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int mt8183_get_apll_by_name(struct mtk_base_afe *afe, const char *name)
{
	if (strcmp(name, APLL1_W_NAME) == 0)
		return MT8183_APLL1;
	else
		return MT8183_APLL2;
}