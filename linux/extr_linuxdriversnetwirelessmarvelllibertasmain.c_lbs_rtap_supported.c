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
struct lbs_private {int fwcapinfo; int /*<<< orphan*/  fwrelease; } ;

/* Variables and functions */
 int MESH_CAPINFO_ENABLE_MASK ; 
 scalar_t__ MRVL_FW_MAJOR_REV (int /*<<< orphan*/ ) ; 
 scalar_t__ MRVL_FW_V10 ; 
 scalar_t__ MRVL_FW_V5 ; 

int lbs_rtap_supported(struct lbs_private *priv)
{
	if (MRVL_FW_MAJOR_REV(priv->fwrelease) == MRVL_FW_V5)
		return 1;

	/* newer firmware use a capability mask */
	return ((MRVL_FW_MAJOR_REV(priv->fwrelease) >= MRVL_FW_V10) &&
		(priv->fwcapinfo & MESH_CAPINFO_ENABLE_MASK));
}