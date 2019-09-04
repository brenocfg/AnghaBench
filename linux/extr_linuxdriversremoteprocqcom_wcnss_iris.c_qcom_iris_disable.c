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
struct qcom_iris {int /*<<< orphan*/  vregs; int /*<<< orphan*/  num_vregs; int /*<<< orphan*/  xo_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qcom_iris_disable(struct qcom_iris *iris)
{
	clk_disable_unprepare(iris->xo_clk);
	regulator_bulk_disable(iris->num_vregs, iris->vregs);
}