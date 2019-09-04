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
struct net_device {struct ctcm_priv* ml_priv; } ;
struct ctcm_priv {int /*<<< orphan*/ * mpcg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_ERROR ; 
 char* MPC_DEVICE_NAME ; 
 int /*<<< orphan*/  MPC_ERROR ; 
 struct net_device* __dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 

__attribute__((used)) static struct net_device *ctcmpc_get_dev(int port_num)
{
	char device[20];
	struct net_device *dev;
	struct ctcm_priv *priv;

	sprintf(device, "%s%i", MPC_DEVICE_NAME, port_num);

	dev = __dev_get_by_name(&init_net, device);

	if (dev == NULL) {
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s: Device not found by name: %s",
					CTCM_FUNTAIL, device);
		return NULL;
	}
	priv = dev->ml_priv;
	if (priv == NULL) {
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): dev->ml_priv is NULL",
					CTCM_FUNTAIL, device);
		return NULL;
	}
	if (priv->mpcg == NULL) {
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): priv->mpcg is NULL",
					CTCM_FUNTAIL, device);
		return NULL;
	}
	return dev;
}