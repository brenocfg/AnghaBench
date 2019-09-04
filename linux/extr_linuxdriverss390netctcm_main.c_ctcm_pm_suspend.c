#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ctcm_priv {TYPE_1__** channel; TYPE_2__* fsm; } ;
struct ccwgroup_device {scalar_t__ state; int /*<<< orphan*/ * cdev; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  wait_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 scalar_t__ CCWGROUP_OFFLINE ; 
 size_t CTCM_READ ; 
 int /*<<< orphan*/  CTCM_TIME_5_SEC ; 
 scalar_t__ DEV_STATE_STOPPED ; 
 int EBUSY ; 
 int /*<<< orphan*/  ccw_device_set_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctcm_close (int /*<<< orphan*/ ) ; 
 struct ctcm_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ fsm_getstate (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctcm_pm_suspend(struct ccwgroup_device *gdev)
{
	struct ctcm_priv *priv = dev_get_drvdata(&gdev->dev);

	if (gdev->state == CCWGROUP_OFFLINE)
		return 0;
	netif_device_detach(priv->channel[CTCM_READ]->netdev);
	ctcm_close(priv->channel[CTCM_READ]->netdev);
	if (!wait_event_timeout(priv->fsm->wait_q,
	    fsm_getstate(priv->fsm) == DEV_STATE_STOPPED, CTCM_TIME_5_SEC)) {
		netif_device_attach(priv->channel[CTCM_READ]->netdev);
		return -EBUSY;
	}
	ccw_device_set_offline(gdev->cdev[1]);
	ccw_device_set_offline(gdev->cdev[0]);
	return 0;
}