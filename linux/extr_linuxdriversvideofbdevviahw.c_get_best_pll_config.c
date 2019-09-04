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
struct via_pll_config {int dummy; } ;
struct TYPE_4__ {TYPE_1__* chip_info; } ;
struct TYPE_3__ {int gfx_chip_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  UNICHROME_CLE266 140 
#define  UNICHROME_CN700 139 
#define  UNICHROME_CN750 138 
#define  UNICHROME_CX700 137 
#define  UNICHROME_K400 136 
#define  UNICHROME_K800 135 
#define  UNICHROME_K8M890 134 
#define  UNICHROME_P4M890 133 
#define  UNICHROME_P4M900 132 
#define  UNICHROME_PM800 131 
#define  UNICHROME_VX800 130 
#define  UNICHROME_VX855 129 
#define  UNICHROME_VX900 128 
 int /*<<< orphan*/  cle266_pll_limits ; 
 int /*<<< orphan*/  cx700_pll_limits ; 
 struct via_pll_config get_pll_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  k800_pll_limits ; 
 TYPE_2__* viaparinfo ; 
 int /*<<< orphan*/  vx855_pll_limits ; 

__attribute__((used)) static struct via_pll_config get_best_pll_config(int clk)
{
	struct via_pll_config config;

	switch (viaparinfo->chip_info->gfx_chip_name) {
	case UNICHROME_CLE266:
	case UNICHROME_K400:
		config = get_pll_config(cle266_pll_limits,
			ARRAY_SIZE(cle266_pll_limits), clk);
		break;
	case UNICHROME_K800:
	case UNICHROME_PM800:
	case UNICHROME_CN700:
		config = get_pll_config(k800_pll_limits,
			ARRAY_SIZE(k800_pll_limits), clk);
		break;
	case UNICHROME_CX700:
	case UNICHROME_CN750:
	case UNICHROME_K8M890:
	case UNICHROME_P4M890:
	case UNICHROME_P4M900:
	case UNICHROME_VX800:
		config = get_pll_config(cx700_pll_limits,
			ARRAY_SIZE(cx700_pll_limits), clk);
		break;
	case UNICHROME_VX855:
	case UNICHROME_VX900:
		config = get_pll_config(vx855_pll_limits,
			ARRAY_SIZE(vx855_pll_limits), clk);
		break;
	}

	return config;
}