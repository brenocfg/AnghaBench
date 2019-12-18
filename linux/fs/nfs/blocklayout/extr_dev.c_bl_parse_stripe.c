#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int volumes_count; int /*<<< orphan*/  chunk_size; int /*<<< orphan*/ * volumes; } ;
struct pnfs_block_volume {TYPE_1__ stripe; } ;
struct pnfs_block_dev {int /*<<< orphan*/  map; int /*<<< orphan*/  chunk_size; int /*<<< orphan*/  len; TYPE_2__* children; int /*<<< orphan*/  nr_children; } ;
struct nfs_server {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {scalar_t__ len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bl_map_stripe ; 
 int bl_parse_deviceid (struct nfs_server*,TYPE_2__*,struct pnfs_block_volume*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bl_parse_stripe(struct nfs_server *server, struct pnfs_block_dev *d,
		struct pnfs_block_volume *volumes, int idx, gfp_t gfp_mask)
{
	struct pnfs_block_volume *v = &volumes[idx];
	u64 len = 0;
	int ret, i;

	d->children = kcalloc(v->stripe.volumes_count,
			sizeof(struct pnfs_block_dev), GFP_KERNEL);
	if (!d->children)
		return -ENOMEM;

	for (i = 0; i < v->stripe.volumes_count; i++) {
		ret = bl_parse_deviceid(server, &d->children[i],
				volumes, v->stripe.volumes[i], gfp_mask);
		if (ret)
			return ret;

		d->nr_children++;
		len += d->children[i].len;
	}

	d->len = len;
	d->chunk_size = v->stripe.chunk_size;
	d->map = bl_map_stripe;
	return 0;
}