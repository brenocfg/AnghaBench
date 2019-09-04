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
struct mt2701_i2s_path {int /*<<< orphan*/  asrco_ck; int /*<<< orphan*/ * hop_ck; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

void mt2701_afe_disable_i2s(struct mtk_base_afe *afe,
			    struct mt2701_i2s_path *i2s_path,
			    int dir)
{
	clk_disable_unprepare(i2s_path->hop_ck[dir]);
	clk_disable_unprepare(i2s_path->asrco_ck);
}