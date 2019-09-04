#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {struct pcmcia_device* priv; struct pcmcia_device* p_dev; } ;
typedef  struct pcmcia_device scsi_info_t ;
struct TYPE_3__ {struct pcmcia_device* ScsiInfo; } ;
typedef  TYPE_1__ nsp_hw_data ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NSP_DEBUG_INIT ; 
 struct pcmcia_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nsp_cs_config (struct pcmcia_device*) ; 
 TYPE_1__ nsp_data_base ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int nsp_cs_probe(struct pcmcia_device *link)
{
	scsi_info_t  *info;
	nsp_hw_data  *data = &nsp_data_base;
	int ret;

	nsp_dbg(NSP_DEBUG_INIT, "in");

	/* Create new SCSI device */
	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL) { return -ENOMEM; }
	info->p_dev = link;
	link->priv = info;
	data->ScsiInfo = info;

	nsp_dbg(NSP_DEBUG_INIT, "info=0x%p", info);

	ret = nsp_cs_config(link);

	nsp_dbg(NSP_DEBUG_INIT, "link=0x%p", link);
	return ret;
}