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
struct nfc_mei_phy {int /*<<< orphan*/  hdev; } ;
struct mei_cl_device {int dummy; } ;

/* Variables and functions */
 struct nfc_mei_phy* mei_cldev_get_drvdata (struct mei_cl_device*) ; 
 int /*<<< orphan*/  microread_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_mei_phy_free (struct nfc_mei_phy*) ; 

__attribute__((used)) static int microread_mei_remove(struct mei_cl_device *cldev)
{
	struct nfc_mei_phy *phy = mei_cldev_get_drvdata(cldev);

	microread_remove(phy->hdev);

	nfc_mei_phy_free(phy);

	return 0;
}