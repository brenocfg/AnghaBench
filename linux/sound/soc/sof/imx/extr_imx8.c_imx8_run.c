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
struct snd_sof_dev {int /*<<< orphan*/  dev; scalar_t__ private; } ;
struct imx8_priv {int /*<<< orphan*/  sc_ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_C_OFS_AUDIO ; 
 int /*<<< orphan*/  IMX_SC_C_OFS_IRQ ; 
 int /*<<< orphan*/  IMX_SC_C_OFS_PERIPH ; 
 int /*<<< orphan*/  IMX_SC_C_OFS_SEL ; 
 int /*<<< orphan*/  IMX_SC_R_DSP ; 
 int /*<<< orphan*/  RESET_VECTOR_VADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int imx_sc_misc_set_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imx_sc_pm_cpu_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx8_run(struct snd_sof_dev *sdev)
{
	struct imx8_priv *dsp_priv = (struct imx8_priv *)sdev->private;
	int ret;

	ret = imx_sc_misc_set_control(dsp_priv->sc_ipc, IMX_SC_R_DSP,
				      IMX_SC_C_OFS_SEL, 1);
	if (ret < 0) {
		dev_err(sdev->dev, "Error system address offset source select\n");
		return ret;
	}

	ret = imx_sc_misc_set_control(dsp_priv->sc_ipc, IMX_SC_R_DSP,
				      IMX_SC_C_OFS_AUDIO, 0x80);
	if (ret < 0) {
		dev_err(sdev->dev, "Error system address offset of AUDIO\n");
		return ret;
	}

	ret = imx_sc_misc_set_control(dsp_priv->sc_ipc, IMX_SC_R_DSP,
				      IMX_SC_C_OFS_PERIPH, 0x5A);
	if (ret < 0) {
		dev_err(sdev->dev, "Error system address offset of PERIPH %d\n",
			ret);
		return ret;
	}

	ret = imx_sc_misc_set_control(dsp_priv->sc_ipc, IMX_SC_R_DSP,
				      IMX_SC_C_OFS_IRQ, 0x51);
	if (ret < 0) {
		dev_err(sdev->dev, "Error system address offset of IRQ\n");
		return ret;
	}

	imx_sc_pm_cpu_start(dsp_priv->sc_ipc, IMX_SC_R_DSP, true,
			    RESET_VECTOR_VADDR);

	return 0;
}