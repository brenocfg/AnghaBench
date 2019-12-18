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
struct z_erofs_maprecorder {int /*<<< orphan*/  inode; } ;
struct TYPE_2__ {unsigned int datalayout; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* EROFS_I (int /*<<< orphan*/ ) ; 
 unsigned int const EROFS_INODE_FLAT_COMPRESSION ; 
 unsigned int const EROFS_INODE_FLAT_COMPRESSION_LEGACY ; 
 int compacted_load_cluster_from_disk (struct z_erofs_maprecorder*,unsigned int) ; 
 int vle_legacy_load_cluster_from_disk (struct z_erofs_maprecorder*,unsigned int) ; 

__attribute__((used)) static int vle_load_cluster_from_disk(struct z_erofs_maprecorder *m,
				      unsigned int lcn)
{
	const unsigned int datamode = EROFS_I(m->inode)->datalayout;

	if (datamode == EROFS_INODE_FLAT_COMPRESSION_LEGACY)
		return vle_legacy_load_cluster_from_disk(m, lcn);

	if (datamode == EROFS_INODE_FLAT_COMPRESSION)
		return compacted_load_cluster_from_disk(m, lcn);

	return -EINVAL;
}