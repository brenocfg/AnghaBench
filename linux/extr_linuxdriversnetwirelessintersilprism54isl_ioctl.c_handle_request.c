#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct obj_mlme {scalar_t__ state; int code; int /*<<< orphan*/  address; } ;
struct TYPE_5__ {int /*<<< orphan*/  acl; } ;
typedef  TYPE_1__ islpci_private ;
typedef  enum oid_num_t { ____Placeholder_oid_num_t } oid_num_t ;

/* Variables and functions */
 scalar_t__ DOT11_STATE_ASSOCING ; 
 scalar_t__ DOT11_STATE_AUTHING ; 
 scalar_t__ mgt_mlme_answer (TYPE_1__*) ; 
 int /*<<< orphan*/  mgt_set_request (TYPE_1__*,int,int /*<<< orphan*/ ,struct obj_mlme*) ; 
 scalar_t__ prism54_mac_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_request(islpci_private *priv, struct obj_mlme *mlme, enum oid_num_t oid)
{
	if (((mlme->state == DOT11_STATE_AUTHING) ||
	     (mlme->state == DOT11_STATE_ASSOCING))
	    && mgt_mlme_answer(priv)) {
		/* Someone is requesting auth and we must respond. Just send back
		 * the trap with error code set accordingly.
		 */
		mlme->code = prism54_mac_accept(&priv->acl,
						mlme->address) ? 0 : 1;
		mgt_set_request(priv, oid, 0, mlme);
	}
}