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
struct media_entity {scalar_t__ function; } ;
struct v4l2_subdev {int /*<<< orphan*/  index; TYPE_2__* dev; struct media_entity entity; } ;
struct v4l2_fwnode_endpoint {int dummy; } ;
struct media_pad {int /*<<< orphan*/  index; TYPE_2__* dev; struct media_entity entity; } ;
struct device_node {int dummy; } ;
struct csi_priv {int /*<<< orphan*/  md; TYPE_1__* src_sd; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {struct media_entity entity; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPIPE ; 
 int /*<<< orphan*/  IMX_MEDIA_GRP_ID_CSI2 ; 
 scalar_t__ IS_ERR (struct v4l2_subdev*) ; 
 scalar_t__ MEDIA_ENT_F_VID_MUX ; 
 int PTR_ERR (struct v4l2_subdev*) ; 
 struct v4l2_subdev* imx_media_find_upstream_pad (int /*<<< orphan*/ ,struct media_entity*,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* imx_media_find_upstream_subdev (int /*<<< orphan*/ ,struct media_entity*,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 struct device_node* of_graph_get_port_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int csi_get_upstream_endpoint(struct csi_priv *priv,
				     struct v4l2_fwnode_endpoint *ep)
{
	struct device_node *endpoint, *port;
	struct media_entity *src;
	struct v4l2_subdev *sd;
	struct media_pad *pad;

	if (!priv->src_sd)
		return -EPIPE;

	src = &priv->src_sd->entity;

	if (src->function == MEDIA_ENT_F_VID_MUX) {
		/*
		 * CSI is connected directly to video mux, skip up to
		 * CSI-2 receiver if it is in the path, otherwise stay
		 * with video mux.
		 */
		sd = imx_media_find_upstream_subdev(priv->md, src,
						    IMX_MEDIA_GRP_ID_CSI2);
		if (!IS_ERR(sd))
			src = &sd->entity;
	}

	/* get source pad of entity directly upstream from src */
	pad = imx_media_find_upstream_pad(priv->md, src, 0);
	if (IS_ERR(pad))
		return PTR_ERR(pad);

	sd = media_entity_to_v4l2_subdev(pad->entity);

	/*
	 * NOTE: this assumes an OF-graph port id is the same as a
	 * media pad index.
	 */
	port = of_graph_get_port_by_id(sd->dev->of_node, pad->index);
	if (!port)
		return -ENODEV;

	endpoint = of_get_next_child(port, NULL);
	of_node_put(port);
	if (!endpoint)
		return -ENODEV;

	v4l2_fwnode_endpoint_parse(of_fwnode_handle(endpoint), ep);
	of_node_put(endpoint);

	return 0;
}