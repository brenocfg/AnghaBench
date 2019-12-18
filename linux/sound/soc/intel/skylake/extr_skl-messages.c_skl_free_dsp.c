#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  usage_count; int /*<<< orphan*/  state; } ;
struct skl_dev {TYPE_4__* dsp; TYPE_2__ cores; TYPE_1__* dsp_ops; } ;
struct hdac_bus {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ lpe; } ;
struct TYPE_8__ {TYPE_3__ addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ ,struct skl_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct hdac_bus* skl_to_bus (struct skl_dev*) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_ppcap_int_enable (struct hdac_bus*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct skl_dev*) ; 

int skl_free_dsp(struct skl_dev *skl)
{
	struct hdac_bus *bus = skl_to_bus(skl);

	/* disable  ppcap interrupt */
	snd_hdac_ext_bus_ppcap_int_enable(bus, false);

	skl->dsp_ops->cleanup(bus->dev, skl);

	kfree(skl->cores.state);
	kfree(skl->cores.usage_count);

	if (skl->dsp->addr.lpe)
		iounmap(skl->dsp->addr.lpe);

	return 0;
}