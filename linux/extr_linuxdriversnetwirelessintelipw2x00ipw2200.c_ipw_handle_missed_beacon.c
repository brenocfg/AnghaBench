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
struct ipw_priv {int notif_missed_beacons; int disassociate_threshold; int status; int roaming_threshold; int /*<<< orphan*/  abort_scan; int /*<<< orphan*/  request_scan; int /*<<< orphan*/  disassociate; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  IPW_DEBUG_NOTIF (char*,int) ; 
 int IPW_DL_ASSOC ; 
 int IPW_DL_INFO ; 
 int IPW_DL_NOTIF ; 
 int IPW_DL_STATE ; 
 int IPW_MB_SCAN_CANCEL_THRESHOLD ; 
 int STATUS_ASSOCIATED ; 
 int STATUS_ROAMING ; 
 int STATUS_SCANNING ; 
 scalar_t__ roaming ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipw_handle_missed_beacon(struct ipw_priv *priv,
					    int missed_count)
{
	priv->notif_missed_beacons = missed_count;

	if (missed_count > priv->disassociate_threshold &&
	    priv->status & STATUS_ASSOCIATED) {
		/* If associated and we've hit the missed
		 * beacon threshold, disassociate, turn
		 * off roaming, and abort any active scans */
		IPW_DEBUG(IPW_DL_INFO | IPW_DL_NOTIF |
			  IPW_DL_STATE | IPW_DL_ASSOC,
			  "Missed beacon: %d - disassociate\n", missed_count);
		priv->status &= ~STATUS_ROAMING;
		if (priv->status & STATUS_SCANNING) {
			IPW_DEBUG(IPW_DL_INFO | IPW_DL_NOTIF |
				  IPW_DL_STATE,
				  "Aborting scan with missed beacon.\n");
			schedule_work(&priv->abort_scan);
		}

		schedule_work(&priv->disassociate);
		return;
	}

	if (priv->status & STATUS_ROAMING) {
		/* If we are currently roaming, then just
		 * print a debug statement... */
		IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE,
			  "Missed beacon: %d - roam in progress\n",
			  missed_count);
		return;
	}

	if (roaming &&
	    (missed_count > priv->roaming_threshold &&
	     missed_count <= priv->disassociate_threshold)) {
		/* If we are not already roaming, set the ROAM
		 * bit in the status and kick off a scan.
		 * This can happen several times before we reach
		 * disassociate_threshold. */
		IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE,
			  "Missed beacon: %d - initiate "
			  "roaming\n", missed_count);
		if (!(priv->status & STATUS_ROAMING)) {
			priv->status |= STATUS_ROAMING;
			if (!(priv->status & STATUS_SCANNING))
				schedule_delayed_work(&priv->request_scan, 0);
		}
		return;
	}

	if (priv->status & STATUS_SCANNING &&
	    missed_count > IPW_MB_SCAN_CANCEL_THRESHOLD) {
		/* Stop scan to keep fw from getting
		 * stuck (only if we aren't roaming --
		 * otherwise we'll never scan more than 2 or 3
		 * channels..) */
		IPW_DEBUG(IPW_DL_INFO | IPW_DL_NOTIF | IPW_DL_STATE,
			  "Aborting scan with missed beacon.\n");
		schedule_work(&priv->abort_scan);
	}

	IPW_DEBUG_NOTIF("Missed beacon: %d\n", missed_count);
}