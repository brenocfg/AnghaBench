#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct ncsi_rsp_gps_pkt {TYPE_2__ rsp; } ;
struct ncsi_request {int /*<<< orphan*/  rsp; struct ncsi_dev_priv* ndp; } ;
struct ncsi_package {int dummy; } ;
struct ncsi_dev_priv {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,struct ncsi_package**,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ncsi_rsp_handler_gps(struct ncsi_request *nr)
{
	struct ncsi_rsp_gps_pkt *rsp;
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct ncsi_package *np;

	/* Find the package */
	rsp = (struct ncsi_rsp_gps_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      &np, NULL);
	if (!np)
		return -ENODEV;

	return 0;
}