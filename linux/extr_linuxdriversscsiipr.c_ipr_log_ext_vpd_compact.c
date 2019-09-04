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
struct ipr_hostrcb {int dummy; } ;
struct ipr_ext_vpd {int /*<<< orphan*/ * wwid; int /*<<< orphan*/  vpd; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_hcam_err (struct ipr_hostrcb*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_log_vpd_compact (char*,struct ipr_hostrcb*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_log_ext_vpd_compact(char *prefix, struct ipr_hostrcb *hostrcb,
				    struct ipr_ext_vpd *vpd)
{
	ipr_log_vpd_compact(prefix, hostrcb, &vpd->vpd);
	ipr_hcam_err(hostrcb, "%s WWN: %08X%08X\n", prefix,
		     be32_to_cpu(vpd->wwid[0]), be32_to_cpu(vpd->wwid[1]));
}