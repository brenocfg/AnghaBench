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
struct pcmcia_socket {int state; scalar_t__ functions; int pcmcia_pfc; int /*<<< orphan*/  dev; int /*<<< orphan*/  ops_mutex; scalar_t__ fake_cis; } ;
struct TYPE_3__ {int nfn; } ;
typedef  TYPE_1__ cistpl_longlink_mfc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_FN_ALL ; 
 int /*<<< orphan*/  CISTPL_LONGLINK_MFC ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_rescan_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pccard_read_tuple (struct pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pcmcia_bus_type ; 
 int /*<<< orphan*/  pcmcia_card_add (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  pcmcia_card_remove (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_device_add (struct pcmcia_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_requery_callback ; 

__attribute__((used)) static void pcmcia_requery(struct pcmcia_socket *s)
{
	int has_pfc;

	if (!(s->state & SOCKET_PRESENT))
		return;

	if (s->functions == 0) {
		pcmcia_card_add(s);
		return;
	}

	/* some device information might have changed because of a CIS
	 * update or because we can finally read it correctly... so
	 * determine it again, overwriting old values if necessary. */
	bus_for_each_dev(&pcmcia_bus_type, NULL, NULL, pcmcia_requery_callback);

	/* if the CIS changed, we need to check whether the number of
	 * functions changed. */
	if (s->fake_cis) {
		int old_funcs, new_funcs;
		cistpl_longlink_mfc_t mfc;

		/* does this cis override add or remove functions? */
		old_funcs = s->functions;

		if (!pccard_read_tuple(s, BIND_FN_ALL, CISTPL_LONGLINK_MFC,
					&mfc))
			new_funcs = mfc.nfn;
		else
			new_funcs = 1;
		if (old_funcs != new_funcs) {
			/* we need to re-start */
			pcmcia_card_remove(s, NULL);
			s->functions = 0;
			pcmcia_card_add(s);
		}
	}

	/* If the PCMCIA device consists of two pseudo devices,
	 * call pcmcia_device_add() -- which will fail if both
	 * devices are already registered. */
	mutex_lock(&s->ops_mutex);
	has_pfc = s->pcmcia_pfc;
	mutex_unlock(&s->ops_mutex);
	if (has_pfc)
		pcmcia_device_add(s, 0);

	/* we re-scan all devices, not just the ones connected to this
	 * socket. This does not matter, though. */
	if (bus_rescan_devices(&pcmcia_bus_type))
		dev_warn(&s->dev, "rescanning the bus failed\n");
}