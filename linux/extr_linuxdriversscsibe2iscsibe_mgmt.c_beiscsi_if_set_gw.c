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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct beiscsi_hba {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * addr; } ;
struct be_cmd_get_def_gateway_resp {TYPE_1__ ip_addr; } ;
typedef  int /*<<< orphan*/  gw_resp ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  IP_ACTION_ADD ; 
 int /*<<< orphan*/  IP_ACTION_DEL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int beiscsi_if_get_gw (struct beiscsi_hba*,int /*<<< orphan*/ ,struct be_cmd_get_def_gateway_resp*) ; 
 int beiscsi_if_mod_gw (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  beiscsi_if_zero_ip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct be_cmd_get_def_gateway_resp*,int /*<<< orphan*/ ,int) ; 

int beiscsi_if_set_gw(struct beiscsi_hba *phba, u32 ip_type, u8 *gw)
{
	struct be_cmd_get_def_gateway_resp gw_resp;
	int rt_val;

	memset(&gw_resp, 0, sizeof(gw_resp));
	rt_val = beiscsi_if_get_gw(phba, ip_type, &gw_resp);
	if (rt_val) {
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
			    "BG_%d : Failed to Get Gateway Addr\n");
		return rt_val;
	}

	if (!beiscsi_if_zero_ip(gw_resp.ip_addr.addr, ip_type)) {
		rt_val = beiscsi_if_mod_gw(phba, IP_ACTION_DEL, ip_type,
					   gw_resp.ip_addr.addr);
		if (rt_val) {
			beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
				    "BG_%d : Failed to clear Gateway Addr Set\n");
			return rt_val;
		}
	}

	rt_val = beiscsi_if_mod_gw(phba, IP_ACTION_ADD, ip_type, gw);
	if (rt_val)
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
			    "BG_%d : Failed to Set Gateway Addr\n");

	return rt_val;
}