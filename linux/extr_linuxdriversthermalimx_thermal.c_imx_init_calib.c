#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct imx_thermal_data {int c1; int c2; TYPE_1__* socdata; } ;
struct TYPE_2__ {scalar_t__ version; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TEMPMON_IMX7D ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct imx_thermal_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int imx_init_calib(struct platform_device *pdev, u32 ocotp_ana1)
{
	struct imx_thermal_data *data = platform_get_drvdata(pdev);
	int n1;
	u64 temp64;

	if (ocotp_ana1 == 0 || ocotp_ana1 == ~0) {
		dev_err(&pdev->dev, "invalid sensor calibration data\n");
		return -EINVAL;
	}

	/*
	 * On i.MX7D, we only use the calibration data at 25C to get the temp,
	 * Tmeas = ( Nmeas - n1) + 25; n1 is the fuse value for 25C.
	 */
	if (data->socdata->version == TEMPMON_IMX7D) {
		data->c1 = (ocotp_ana1 >> 9) & 0x1ff;
		return 0;
	}

	/*
	 * The sensor is calibrated at 25 °C (aka T1) and the value measured
	 * (aka N1) at this temperature is provided in bits [31:20] in the
	 * i.MX's OCOTP value ANA1.
	 * To find the actual temperature T, the following formula has to be used
	 * when reading value n from the sensor:
	 *
	 * T = T1 + (N - N1) / (0.4148468 - 0.0015423 * N1) °C + 3.580661 °C
	 *   = [T1' - N1 / (0.4148468 - 0.0015423 * N1) °C] + N / (0.4148468 - 0.0015423 * N1) °C
	 *   = [T1' + N1 / (0.0015423 * N1 - 0.4148468) °C] - N / (0.0015423 * N1 - 0.4148468) °C
	 *   = c2 - c1 * N
	 *
	 * with
	 *
	 *  T1' = 28.580661 °C
	 *   c1 = 1 / (0.0015423 * N1 - 0.4297157) °C
	 *   c2 = T1' + N1 / (0.0015423 * N1 - 0.4148468) °C
	 *      = T1' + N1 * c1
	 */
	n1 = ocotp_ana1 >> 20;

	temp64 = 10000000; /* use 10^7 as fixed point constant for values in formula */
	temp64 *= 1000; /* to get result in °mC */
	do_div(temp64, 15423 * n1 - 4148468);
	data->c1 = temp64;
	data->c2 = n1 * data->c1 + 28581;

	return 0;
}