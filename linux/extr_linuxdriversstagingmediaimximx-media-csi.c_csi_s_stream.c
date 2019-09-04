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
struct v4l2_subdev {int dummy; } ;
struct csi_priv {int stream_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  sink; int /*<<< orphan*/  src_sd; } ;

/* Variables and functions */
 int EPIPE ; 
 int csi_start (struct csi_priv*) ; 
 int /*<<< orphan*/  csi_stop (struct csi_priv*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct csi_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct csi_priv *priv = v4l2_get_subdevdata(sd);
	int ret = 0;

	mutex_lock(&priv->lock);

	if (!priv->src_sd || !priv->sink) {
		ret = -EPIPE;
		goto out;
	}

	/*
	 * enable/disable streaming only if stream_count is
	 * going from 0 to 1 / 1 to 0.
	 */
	if (priv->stream_count != !enable)
		goto update_count;

	if (enable) {
		dev_dbg(priv->dev, "stream ON\n");
		ret = csi_start(priv);
		if (ret)
			goto out;
	} else {
		dev_dbg(priv->dev, "stream OFF\n");
		csi_stop(priv);
	}

update_count:
	priv->stream_count += enable ? 1 : -1;
	if (priv->stream_count < 0)
		priv->stream_count = 0;
out:
	mutex_unlock(&priv->lock);
	return ret;
}