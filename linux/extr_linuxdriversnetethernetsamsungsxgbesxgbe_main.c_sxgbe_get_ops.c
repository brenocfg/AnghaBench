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
struct TYPE_4__ {int /*<<< orphan*/  speed; scalar_t__ duplex; scalar_t__ port; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct sxgbe_ops {TYPE_2__ link; TYPE_1__ mii; int /*<<< orphan*/  mtl; int /*<<< orphan*/  dma; int /*<<< orphan*/  desc; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  SXGBE_MDIO_SCMD_ADD_REG ; 
 int /*<<< orphan*/  SXGBE_MDIO_SCMD_DATA_REG ; 
 int /*<<< orphan*/  SXGBE_SPEED_10G ; 
 int /*<<< orphan*/  sxgbe_get_core_ops () ; 
 int /*<<< orphan*/  sxgbe_get_desc_ops () ; 
 int /*<<< orphan*/  sxgbe_get_dma_ops () ; 
 int /*<<< orphan*/  sxgbe_get_mtl_ops () ; 

__attribute__((used)) static void sxgbe_get_ops(struct sxgbe_ops * const ops_ptr)
{
	ops_ptr->mac		= sxgbe_get_core_ops();
	ops_ptr->desc		= sxgbe_get_desc_ops();
	ops_ptr->dma		= sxgbe_get_dma_ops();
	ops_ptr->mtl		= sxgbe_get_mtl_ops();

	/* set the MDIO communication Address/Data regisers */
	ops_ptr->mii.addr	= SXGBE_MDIO_SCMD_ADD_REG;
	ops_ptr->mii.data	= SXGBE_MDIO_SCMD_DATA_REG;

	/* Assigning the default link settings
	 * no SXGBE defined default values to be set in registers,
	 * so assigning as 0 for port and duplex
	 */
	ops_ptr->link.port	= 0;
	ops_ptr->link.duplex	= 0;
	ops_ptr->link.speed	= SXGBE_SPEED_10G;
}