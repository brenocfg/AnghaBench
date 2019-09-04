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
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  start; int /*<<< orphan*/  volume; } ;
struct pnfs_block_volume {TYPE_1__ slice; } ;
struct pnfs_block_dev {int /*<<< orphan*/  len; int /*<<< orphan*/  disk_offset; } ;
struct nfs_server {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int bl_parse_deviceid (struct nfs_server*,struct pnfs_block_dev*,struct pnfs_block_volume*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bl_parse_slice(struct nfs_server *server, struct pnfs_block_dev *d,
		struct pnfs_block_volume *volumes, int idx, gfp_t gfp_mask)
{
	struct pnfs_block_volume *v = &volumes[idx];
	int ret;

	ret = bl_parse_deviceid(server, d, volumes, v->slice.volume, gfp_mask);
	if (ret)
		return ret;

	d->disk_offset = v->slice.start;
	d->len = v->slice.len;
	return 0;
}