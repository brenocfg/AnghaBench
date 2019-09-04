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
struct ufs_hisi_dev_params {int /*<<< orphan*/  desired_working_mode; int /*<<< orphan*/  hs_rate; int /*<<< orphan*/  tx_pwr_hs; int /*<<< orphan*/  rx_pwr_hs; int /*<<< orphan*/  tx_pwr_pwm; int /*<<< orphan*/  rx_pwr_pwm; int /*<<< orphan*/  pwm_tx_gear; int /*<<< orphan*/  pwm_rx_gear; int /*<<< orphan*/  hs_tx_gear; int /*<<< orphan*/  hs_rx_gear; int /*<<< orphan*/  tx_lanes; int /*<<< orphan*/  rx_lanes; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFS_HISI_LIMIT_DESIRED_MODE ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_HSGEAR_RX ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_HSGEAR_TX ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_HS_RATE ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_NUM_LANES_RX ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_NUM_LANES_TX ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_PWMGEAR_RX ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_PWMGEAR_TX ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_RX_PWR_HS ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_RX_PWR_PWM ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_TX_PWR_HS ; 
 int /*<<< orphan*/  UFS_HISI_LIMIT_TX_PWR_PWM ; 

__attribute__((used)) static void ufs_hisi_set_dev_cap(struct ufs_hisi_dev_params *hisi_param)
{
	hisi_param->rx_lanes = UFS_HISI_LIMIT_NUM_LANES_RX;
	hisi_param->tx_lanes = UFS_HISI_LIMIT_NUM_LANES_TX;
	hisi_param->hs_rx_gear = UFS_HISI_LIMIT_HSGEAR_RX;
	hisi_param->hs_tx_gear = UFS_HISI_LIMIT_HSGEAR_TX;
	hisi_param->pwm_rx_gear = UFS_HISI_LIMIT_PWMGEAR_RX;
	hisi_param->pwm_tx_gear = UFS_HISI_LIMIT_PWMGEAR_TX;
	hisi_param->rx_pwr_pwm = UFS_HISI_LIMIT_RX_PWR_PWM;
	hisi_param->tx_pwr_pwm = UFS_HISI_LIMIT_TX_PWR_PWM;
	hisi_param->rx_pwr_hs = UFS_HISI_LIMIT_RX_PWR_HS;
	hisi_param->tx_pwr_hs = UFS_HISI_LIMIT_TX_PWR_HS;
	hisi_param->hs_rate = UFS_HISI_LIMIT_HS_RATE;
	hisi_param->desired_working_mode = UFS_HISI_LIMIT_DESIRED_MODE;
}