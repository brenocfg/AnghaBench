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
struct TYPE_2__ {int /*<<< orphan*/  wakeup_request; } ;
struct ks_wlan_private {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  rw_dwork; int /*<<< orphan*/  wq; TYPE_1__ sleepstatus; } ;
struct hostif_sleep_request {int dummy; } ;
typedef  enum sleep_mode_type { ____Placeholder_sleep_mode_type } sleep_mode_type ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_SLEEP_REQ ; 
 int SLP_ACTIVE ; 
 int SLP_SLEEP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hif_align_size (int) ; 
 struct hostif_sleep_request* hostif_generic_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send_request_to_device (struct ks_wlan_private*,struct hostif_sleep_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void hostif_sleep_request(struct ks_wlan_private *priv,
			  enum sleep_mode_type mode)
{
	struct hostif_sleep_request *pp;

	if (mode == SLP_SLEEP) {
		pp = hostif_generic_request(sizeof(*pp), HIF_SLEEP_REQ);
		if (!pp)
			return;

		send_request_to_device(priv, pp, hif_align_size(sizeof(*pp)));
	} else if (mode == SLP_ACTIVE) {
		atomic_set(&priv->sleepstatus.wakeup_request, 1);
		queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
	} else {
		netdev_err(priv->net_dev, "invalid mode %ld\n", (long)mode);
		return;
	}
}