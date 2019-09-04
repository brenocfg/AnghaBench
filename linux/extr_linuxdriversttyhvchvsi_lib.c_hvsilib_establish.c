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
struct hvsi_priv {int opened; int /*<<< orphan*/  termno; scalar_t__ established; } ;

/* Variables and functions */
 int /*<<< orphan*/  hvsi_get_packet (struct hvsi_priv*) ; 
 int /*<<< orphan*/  hvsi_send_close (struct hvsi_priv*) ; 
 int /*<<< orphan*/  hvsi_start_handshake (struct hvsi_priv*) ; 
 int /*<<< orphan*/  hvsilib_read_mctrl (struct hvsi_priv*) ; 
 int /*<<< orphan*/  hvsilib_write_mctrl (struct hvsi_priv*,int) ; 
 int /*<<< orphan*/  maybe_msleep (int) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

void hvsilib_establish(struct hvsi_priv *pv)
{
	int timeout;

	pr_devel("HVSI@%x: Establishing...\n", pv->termno);

	/* Try for up to 200ms, there can be a packet to
	 * start the process waiting for us...
	 */
	for (timeout = 0; timeout < 20; timeout++) {
		if (pv->established)
			goto established;
		if (!hvsi_get_packet(pv))
			maybe_msleep(10);
	}

	/* Failed, send a close connection packet just
	 * in case
	 */
	pr_devel("HVSI@%x:   ... sending close\n", pv->termno);

	hvsi_send_close(pv);

	/* Then restart handshake */

	pr_devel("HVSI@%x:   ... restarting handshake\n", pv->termno);

	hvsi_start_handshake(pv);

	pr_devel("HVSI@%x:   ... waiting handshake\n", pv->termno);

	/* Try for up to 400ms */
	for (timeout = 0; timeout < 40; timeout++) {
		if (pv->established)
			goto established;
		if (!hvsi_get_packet(pv))
			maybe_msleep(10);
	}

	if (!pv->established) {
		pr_devel("HVSI@%x: Timeout handshaking, giving up !\n",
			 pv->termno);
		return;
	}
 established:
	/* Query modem control lines */

	pr_devel("HVSI@%x:   ... established, reading mctrl\n", pv->termno);

	hvsilib_read_mctrl(pv);

	/* Set our own DTR */

	pr_devel("HVSI@%x:   ... setting mctrl\n", pv->termno);

	hvsilib_write_mctrl(pv, 1);

	/* Set the opened flag so reads are allowed */
	wmb();
	pv->opened = 1;
}