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
struct dwc3_qcom {int /*<<< orphan*/  qscratch_base; } ;

/* Variables and functions */
 int PIPE3_PHYSTATUS_SW ; 
 int PIPE_UTMI_CLK_DIS ; 
 int PIPE_UTMI_CLK_SEL ; 
 int /*<<< orphan*/  QSCRATCH_GENERAL_CFG ; 
 int /*<<< orphan*/  dwc3_qcom_clrbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dwc3_qcom_setbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void dwc3_qcom_select_utmi_clk(struct dwc3_qcom *qcom)
{
	/* Configure dwc3 to use UTMI clock as PIPE clock not present */
	dwc3_qcom_setbits(qcom->qscratch_base, QSCRATCH_GENERAL_CFG,
			  PIPE_UTMI_CLK_DIS);

	usleep_range(100, 1000);

	dwc3_qcom_setbits(qcom->qscratch_base, QSCRATCH_GENERAL_CFG,
			  PIPE_UTMI_CLK_SEL | PIPE3_PHYSTATUS_SW);

	usleep_range(100, 1000);

	dwc3_qcom_clrbits(qcom->qscratch_base, QSCRATCH_GENERAL_CFG,
			  PIPE_UTMI_CLK_DIS);
}