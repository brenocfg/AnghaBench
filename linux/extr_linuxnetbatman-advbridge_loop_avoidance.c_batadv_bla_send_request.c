#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct batadv_bla_backbone_gw {int /*<<< orphan*/  request_sent; TYPE_2__* bat_priv; int /*<<< orphan*/  vid; int /*<<< orphan*/  orig; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_requests; } ;
struct TYPE_5__ {TYPE_1__ bla; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CLAIM_TYPE_REQUEST ; 
 int /*<<< orphan*/  BATADV_DBG_BLA ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  batadv_bla_del_backbone_claims (struct batadv_bla_backbone_gw*) ; 
 int /*<<< orphan*/  batadv_bla_send_claim (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_bla_send_request(struct batadv_bla_backbone_gw *backbone_gw)
{
	/* first, remove all old entries */
	batadv_bla_del_backbone_claims(backbone_gw);

	batadv_dbg(BATADV_DBG_BLA, backbone_gw->bat_priv,
		   "Sending REQUEST to %pM\n", backbone_gw->orig);

	/* send request */
	batadv_bla_send_claim(backbone_gw->bat_priv, backbone_gw->orig,
			      backbone_gw->vid, BATADV_CLAIM_TYPE_REQUEST);

	/* no local broadcasts should be sent or received, for now. */
	if (!atomic_read(&backbone_gw->request_sent)) {
		atomic_inc(&backbone_gw->bat_priv->bla.num_requests);
		atomic_set(&backbone_gw->request_sent, 1);
	}
}