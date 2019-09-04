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
typedef  int /*<<< orphan*/  u32 ;
struct ks_wlan_private {int dummy; } ;
struct hostif_power_mgmt_request {void* receive_dtims; void* wake_up; void* mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_POWER_MGMT_REQ ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hif_align_size (int) ; 
 struct hostif_power_mgmt_request* hostif_generic_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_request_to_device (struct ks_wlan_private*,struct hostif_power_mgmt_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void hostif_power_mgmt_request(struct ks_wlan_private *priv,
			       u32 mode, u32 wake_up, u32 receive_dtims)
{
	struct hostif_power_mgmt_request *pp;

	pp = hostif_generic_request(sizeof(*pp), HIF_POWER_MGMT_REQ);
	if (!pp)
		return;

	pp->mode = cpu_to_le32(mode);
	pp->wake_up = cpu_to_le32(wake_up);
	pp->receive_dtims = cpu_to_le32(receive_dtims);

	send_request_to_device(priv, pp, hif_align_size(sizeof(*pp)));
}