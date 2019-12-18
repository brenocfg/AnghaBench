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
struct address_space {scalar_t__ nrpages; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int nfs_wb_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_mapping_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfs_sync_mapping(struct address_space *mapping)
{
	int ret = 0;

	if (mapping->nrpages != 0) {
		unmap_mapping_range(mapping, 0, 0, 0);
		ret = nfs_wb_all(mapping->host);
	}
	return ret;
}