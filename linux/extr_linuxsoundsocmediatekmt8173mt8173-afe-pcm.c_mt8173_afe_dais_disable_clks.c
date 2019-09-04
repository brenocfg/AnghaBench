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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 

__attribute__((used)) static void mt8173_afe_dais_disable_clks(struct mtk_base_afe *afe,
					 struct clk *m_ck, struct clk *b_ck)
{
	if (m_ck)
		clk_disable_unprepare(m_ck);
	if (b_ck)
		clk_disable_unprepare(b_ck);
}