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
struct inode {TYPE_1__* i_mapping; } ;
struct erofs_inode {scalar_t__ datalayout; int /*<<< orphan*/  flags; int /*<<< orphan*/  z_logical_clusterbits; int /*<<< orphan*/ * z_physical_clusterbits; scalar_t__* z_algorithmtype; scalar_t__ z_advise; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 struct erofs_inode* EROFS_I (struct inode*) ; 
 scalar_t__ EROFS_INODE_FLAT_COMPRESSION_LEGACY ; 
 int /*<<< orphan*/  EROFS_I_Z_INITED_BIT ; 
 int /*<<< orphan*/  LOG_BLOCK_SIZE ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z_erofs_vle_normalaccess_aops ; 

int z_erofs_fill_inode(struct inode *inode)
{
	struct erofs_inode *const vi = EROFS_I(inode);

	if (vi->datalayout == EROFS_INODE_FLAT_COMPRESSION_LEGACY) {
		vi->z_advise = 0;
		vi->z_algorithmtype[0] = 0;
		vi->z_algorithmtype[1] = 0;
		vi->z_logical_clusterbits = LOG_BLOCK_SIZE;
		vi->z_physical_clusterbits[0] = vi->z_logical_clusterbits;
		vi->z_physical_clusterbits[1] = vi->z_logical_clusterbits;
		set_bit(EROFS_I_Z_INITED_BIT, &vi->flags);
	}

	inode->i_mapping->a_ops = &z_erofs_vle_normalaccess_aops;
	return 0;
}