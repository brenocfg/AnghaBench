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
struct ntb_dev {int dummy; } ;
struct intel_ntb_dev {TYPE_1__* peer_reg; int /*<<< orphan*/  peer_addr; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  db_bell; } ;

/* Variables and functions */
 int ndev_db_addr (struct intel_ntb_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_ntb_dev* ntb_ndev (struct ntb_dev*) ; 

int intel_ntb_peer_db_addr(struct ntb_dev *ntb, phys_addr_t *db_addr,
			   resource_size_t *db_size)
{
	struct intel_ntb_dev *ndev = ntb_ndev(ntb);

	return ndev_db_addr(ndev, db_addr, db_size, ndev->peer_addr,
			    ndev->peer_reg->db_bell);
}