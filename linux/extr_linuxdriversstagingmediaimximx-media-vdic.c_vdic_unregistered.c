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
struct vdic_priv {int /*<<< orphan*/  ctrl_hdlr; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 struct vdic_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void vdic_unregistered(struct v4l2_subdev *sd)
{
	struct vdic_priv *priv = v4l2_get_subdevdata(sd);

	v4l2_ctrl_handler_free(&priv->ctrl_hdlr);
}