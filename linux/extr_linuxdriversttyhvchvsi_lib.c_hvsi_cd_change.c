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
struct hvsi_priv {int /*<<< orphan*/  termno; scalar_t__ opened; int /*<<< orphan*/  is_console; int /*<<< orphan*/  mctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCM_CD ; 
 int /*<<< orphan*/  hvsi_send_close (struct hvsi_priv*) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hvsi_cd_change(struct hvsi_priv *pv, int cd)
{
	if (cd)
		pv->mctrl |= TIOCM_CD;
	else {
		pv->mctrl &= ~TIOCM_CD;

		/* We copy the existing hvsi driver semantics
		 * here which are to trigger a hangup when
		 * we get a carrier loss.
		 * Closing our connection to the server will
		 * do just that.
		 */
		if (!pv->is_console && pv->opened) {
			pr_devel("HVSI@%x Carrier lost, hanging up !\n",
				 pv->termno);
			hvsi_send_close(pv);
		}
	}
}