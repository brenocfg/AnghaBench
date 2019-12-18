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
struct imx_dsp_ipc {int dummy; } ;
struct imx8_priv {int /*<<< orphan*/  sdev; } ;

/* Variables and functions */
 struct imx8_priv* imx_dsp_get_data (struct imx_dsp_ipc*) ; 
 int /*<<< orphan*/  snd_sof_ipc_msgs_rx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx8_dsp_handle_request(struct imx_dsp_ipc *ipc)
{
	struct imx8_priv *priv = imx_dsp_get_data(ipc);

	snd_sof_ipc_msgs_rx(priv->sdev);
}