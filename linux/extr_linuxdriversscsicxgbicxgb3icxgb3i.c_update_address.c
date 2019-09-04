#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cxgbi_hba {scalar_t__ ipv4addr; TYPE_1__* ndev; TYPE_1__* vdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ cxgb3i_get_private_ipv4addr (TYPE_1__*) ; 
 int /*<<< orphan*/  cxgb3i_set_private_ipv4addr (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void update_address(struct cxgbi_hba *chba)
{
	if (chba->ipv4addr) {
		if (chba->vdev &&
		    chba->ipv4addr != cxgb3i_get_private_ipv4addr(chba->vdev)) {
			cxgb3i_set_private_ipv4addr(chba->vdev, chba->ipv4addr);
			cxgb3i_set_private_ipv4addr(chba->ndev, 0);
			pr_info("%s set %pI4.\n",
				chba->vdev->name, &chba->ipv4addr);
		} else if (chba->ipv4addr !=
				cxgb3i_get_private_ipv4addr(chba->ndev)) {
			cxgb3i_set_private_ipv4addr(chba->ndev, chba->ipv4addr);
			pr_info("%s set %pI4.\n",
				chba->ndev->name, &chba->ipv4addr);
		}
	} else if (cxgb3i_get_private_ipv4addr(chba->ndev)) {
		if (chba->vdev)
			cxgb3i_set_private_ipv4addr(chba->vdev, 0);
		cxgb3i_set_private_ipv4addr(chba->ndev, 0);
	}
}