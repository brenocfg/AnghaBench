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
struct sof_ipc_reply {int error; } ;
struct TYPE_2__ {int size; int cmd; } ;
struct sof_ipc_pipe_comp_connect {int /*<<< orphan*/  list; struct sof_ipc_pipe_comp_connect* private; struct snd_soc_dapm_route* route; TYPE_1__ hdr; int /*<<< orphan*/  sink_id; int /*<<< orphan*/  source_id; struct snd_sof_dev* sdev; } ;
struct snd_sof_widget {scalar_t__ id; int /*<<< orphan*/  comp_id; } ;
struct snd_sof_route {int /*<<< orphan*/  list; struct snd_sof_route* private; struct snd_soc_dapm_route* route; TYPE_1__ hdr; int /*<<< orphan*/  sink_id; int /*<<< orphan*/  source_id; struct snd_sof_dev* sdev; } ;
struct snd_sof_dev {int /*<<< orphan*/  route_list; int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
struct snd_soc_dobj {struct sof_ipc_pipe_comp_connect* private; } ;
struct snd_soc_dapm_route {char* control; scalar_t__ source; scalar_t__ sink; struct snd_soc_dobj dobj; } ;
struct snd_soc_component {int dummy; } ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SOF_IPC_GLB_TPLG_MSG ; 
 int SOF_IPC_TPLG_COMP_CONNECT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  kfree (struct sof_ipc_pipe_comp_connect*) ; 
 struct sof_ipc_pipe_comp_connect* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 scalar_t__ snd_soc_dapm_buffer ; 
 scalar_t__ snd_soc_dapm_out_drv ; 
 scalar_t__ snd_soc_dapm_output ; 
 struct snd_sof_widget* snd_sof_find_swidget (struct snd_sof_dev*,char*) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_pipe_comp_connect*,int,struct sof_ipc_reply*,int) ; 

__attribute__((used)) static int sof_route_load(struct snd_soc_component *scomp, int index,
			  struct snd_soc_dapm_route *route)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	struct sof_ipc_pipe_comp_connect *connect;
	struct snd_sof_widget *source_swidget, *sink_swidget;
	struct snd_soc_dobj *dobj = &route->dobj;
	struct snd_sof_route *sroute;
	struct sof_ipc_reply reply;
	int ret = 0;

	/* allocate memory for sroute and connect */
	sroute = kzalloc(sizeof(*sroute), GFP_KERNEL);
	if (!sroute)
		return -ENOMEM;

	sroute->sdev = sdev;

	connect = kzalloc(sizeof(*connect), GFP_KERNEL);
	if (!connect) {
		kfree(sroute);
		return -ENOMEM;
	}

	connect->hdr.size = sizeof(*connect);
	connect->hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_COMP_CONNECT;

	dev_dbg(sdev->dev, "sink %s control %s source %s\n",
		route->sink, route->control ? route->control : "none",
		route->source);

	/* source component */
	source_swidget = snd_sof_find_swidget(sdev, (char *)route->source);
	if (!source_swidget) {
		dev_err(sdev->dev, "error: source %s not found\n",
			route->source);
		ret = -EINVAL;
		goto err;
	}

	/*
	 * Virtual widgets of type output/out_drv may be added in topology
	 * for compatibility. These are not handled by the FW.
	 * So, don't send routes whose source/sink widget is of such types
	 * to the DSP.
	 */
	if (source_swidget->id == snd_soc_dapm_out_drv ||
	    source_swidget->id == snd_soc_dapm_output)
		goto err;

	connect->source_id = source_swidget->comp_id;

	/* sink component */
	sink_swidget = snd_sof_find_swidget(sdev, (char *)route->sink);
	if (!sink_swidget) {
		dev_err(sdev->dev, "error: sink %s not found\n",
			route->sink);
		ret = -EINVAL;
		goto err;
	}

	/*
	 * Don't send routes whose sink widget is of type
	 * output or out_drv to the DSP
	 */
	if (sink_swidget->id == snd_soc_dapm_out_drv ||
	    sink_swidget->id == snd_soc_dapm_output)
		goto err;

	connect->sink_id = sink_swidget->comp_id;

	/*
	 * For virtual routes, both sink and source are not
	 * buffer. Since only buffer linked to component is supported by
	 * FW, others are reported as error, add check in route function,
	 * do not send it to FW when both source and sink are not buffer
	 */
	if (source_swidget->id != snd_soc_dapm_buffer &&
	    sink_swidget->id != snd_soc_dapm_buffer) {
		dev_dbg(sdev->dev, "warning: neither Linked source component %s nor sink component %s is of buffer type, ignoring link\n",
			route->source, route->sink);
		ret = 0;
		goto err;
	} else {
		ret = sof_ipc_tx_message(sdev->ipc,
					 connect->hdr.cmd,
					 connect, sizeof(*connect),
					 &reply, sizeof(reply));

		/* check IPC return value */
		if (ret < 0) {
			dev_err(sdev->dev, "error: failed to add route sink %s control %s source %s\n",
				route->sink,
				route->control ? route->control : "none",
				route->source);
			goto err;
		}

		/* check IPC reply */
		if (reply.error < 0) {
			dev_err(sdev->dev, "error: DSP failed to add route sink %s control %s source %s result %d\n",
				route->sink,
				route->control ? route->control : "none",
				route->source, reply.error);
			ret = reply.error;
			goto err;
		}

		sroute->route = route;
		dobj->private = sroute;
		sroute->private = connect;

		/* add route to route list */
		list_add(&sroute->list, &sdev->route_list);

		return ret;
	}

err:
	kfree(connect);
	kfree(sroute);
	return ret;
}