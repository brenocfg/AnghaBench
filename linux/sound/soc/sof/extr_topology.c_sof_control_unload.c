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
struct TYPE_2__ {int cmd; int size; } ;
struct sof_ipc_free {TYPE_1__ hdr; int /*<<< orphan*/  id; } ;
struct snd_sof_dev {int /*<<< orphan*/  ipc; int /*<<< orphan*/  dev; } ;
struct snd_sof_control {int /*<<< orphan*/  list; struct snd_sof_control* control_data; int /*<<< orphan*/  comp_id; } ;
struct snd_soc_dobj {struct snd_sof_control* private; } ;
struct snd_soc_component {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  fcomp ;

/* Variables and functions */
 int SOF_IPC_GLB_TPLG_MSG ; 
 int SOF_IPC_TPLG_COMP_FREE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_sof_control*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_free*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sof_control_unload(struct snd_soc_component *scomp,
			      struct snd_soc_dobj *dobj)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	struct sof_ipc_free fcomp;
	struct snd_sof_control *scontrol = dobj->private;

	dev_dbg(sdev->dev, "tplg: unload control name : %s\n", scomp->name);

	fcomp.hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_COMP_FREE;
	fcomp.hdr.size = sizeof(fcomp);
	fcomp.id = scontrol->comp_id;

	kfree(scontrol->control_data);
	list_del(&scontrol->list);
	kfree(scontrol);
	/* send IPC to the DSP */
	return sof_ipc_tx_message(sdev->ipc,
				  fcomp.hdr.cmd, &fcomp, sizeof(fcomp),
				  NULL, 0);
}