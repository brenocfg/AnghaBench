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
struct ufs_qcom_phy {int dummy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ phy_get_drvdata (struct phy*) ; 

struct ufs_qcom_phy *get_ufs_qcom_phy(struct phy *generic_phy)
{
	return (struct ufs_qcom_phy *)phy_get_drvdata(generic_phy);
}