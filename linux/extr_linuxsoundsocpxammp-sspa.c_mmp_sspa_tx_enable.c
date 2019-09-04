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
struct ssp_device {int dummy; } ;

/* Variables and functions */
 unsigned int SSPA_SP_S_EN ; 
 unsigned int SSPA_SP_WEN ; 
 int /*<<< orphan*/  SSPA_TXSP ; 
 unsigned int mmp_sspa_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_sspa_write_reg (struct ssp_device*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void mmp_sspa_tx_enable(struct ssp_device *sspa)
{
	unsigned int sspa_sp;

	sspa_sp = mmp_sspa_read_reg(sspa, SSPA_TXSP);
	sspa_sp |= SSPA_SP_S_EN;
	sspa_sp |= SSPA_SP_WEN;
	mmp_sspa_write_reg(sspa, SSPA_TXSP, sspa_sp);
}