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
struct skl_dev {int /*<<< orphan*/  dsp; } ;
struct hdac_bus {int /*<<< orphan*/  ppcap; } ;

/* Variables and functions */
 int skl_dsp_sleep (int /*<<< orphan*/ ) ; 
 struct hdac_bus* skl_to_bus (struct skl_dev*) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_ppcap_enable (struct hdac_bus*,int) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_ppcap_int_enable (struct hdac_bus*,int) ; 

int skl_suspend_dsp(struct skl_dev *skl)
{
	struct hdac_bus *bus = skl_to_bus(skl);
	int ret;

	/* if ppcap is not supported return 0 */
	if (!bus->ppcap)
		return 0;

	ret = skl_dsp_sleep(skl->dsp);
	if (ret < 0)
		return ret;

	/* disable ppcap interrupt */
	snd_hdac_ext_bus_ppcap_int_enable(bus, false);
	snd_hdac_ext_bus_ppcap_enable(bus, false);

	return 0;
}