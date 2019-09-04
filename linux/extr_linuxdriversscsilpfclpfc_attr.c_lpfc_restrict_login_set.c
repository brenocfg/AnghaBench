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
struct lpfc_vport {int cfg_restrict_login; scalar_t__ port_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 scalar_t__ LPFC_PHYSICAL_PORT ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
lpfc_restrict_login_set(struct lpfc_vport *vport, int val)
{
	if (val < 0 || val > 1) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				 "0425 lpfc_restrict_login attribute cannot "
				 "be set to %d, allowed range is [0, 1]\n",
				 val);
		vport->cfg_restrict_login = 1;
		return -EINVAL;
	}
	if (vport->port_type == LPFC_PHYSICAL_PORT && val != 0) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_INIT,
				 "0468 lpfc_restrict_login must be 0 for "
				 "Physical ports.\n");
		vport->cfg_restrict_login = 0;
		return 0;
	}
	vport->cfg_restrict_login = val;
	return 0;
}