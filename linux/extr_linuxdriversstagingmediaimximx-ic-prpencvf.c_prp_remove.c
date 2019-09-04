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
struct prp_priv {int /*<<< orphan*/  vdev; int /*<<< orphan*/  lock; } ;
struct imx_ic_priv {struct prp_priv* task_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_media_capture_device_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prp_remove(struct imx_ic_priv *ic_priv)
{
	struct prp_priv *priv = ic_priv->task_priv;

	mutex_destroy(&priv->lock);
	imx_media_capture_device_remove(priv->vdev);
}