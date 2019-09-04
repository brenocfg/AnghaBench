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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nd_region {int /*<<< orphan*/  dev; scalar_t__ ro; } ;
struct nd_namespace_io {int /*<<< orphan*/  bb; } ;
struct device {int dummy; } ;
struct nd_btt {TYPE_1__* ndns; struct device dev; } ;
struct btt {unsigned long long rawsize; int lbasize; int sector_size; scalar_t__ init_state; unsigned long long num_arenas; int /*<<< orphan*/ * phys_bb; struct nd_region* nd_region; int /*<<< orphan*/  init_lock; int /*<<< orphan*/  arena_list; struct nd_btt* nd_btt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long long ARENA_MAX_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ INIT_READY ; 
 int btt_blk_init (struct btt*) ; 
 int /*<<< orphan*/  btt_debugfs_init (struct btt*) ; 
 int btt_meta_init (struct btt*) ; 
 int create_arenas (struct btt*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct btt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int discover_arenas (struct btt*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct nd_namespace_io* to_nd_namespace_io (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct btt *btt_init(struct nd_btt *nd_btt, unsigned long long rawsize,
		u32 lbasize, u8 *uuid, struct nd_region *nd_region)
{
	int ret;
	struct btt *btt;
	struct nd_namespace_io *nsio;
	struct device *dev = &nd_btt->dev;

	btt = devm_kzalloc(dev, sizeof(struct btt), GFP_KERNEL);
	if (!btt)
		return NULL;

	btt->nd_btt = nd_btt;
	btt->rawsize = rawsize;
	btt->lbasize = lbasize;
	btt->sector_size = ((lbasize >= 4096) ? 4096 : 512);
	INIT_LIST_HEAD(&btt->arena_list);
	mutex_init(&btt->init_lock);
	btt->nd_region = nd_region;
	nsio = to_nd_namespace_io(&nd_btt->ndns->dev);
	btt->phys_bb = &nsio->bb;

	ret = discover_arenas(btt);
	if (ret) {
		dev_err(dev, "init: error in arena_discover: %d\n", ret);
		return NULL;
	}

	if (btt->init_state != INIT_READY && nd_region->ro) {
		dev_warn(dev, "%s is read-only, unable to init btt metadata\n",
				dev_name(&nd_region->dev));
		return NULL;
	} else if (btt->init_state != INIT_READY) {
		btt->num_arenas = (rawsize / ARENA_MAX_SIZE) +
			((rawsize % ARENA_MAX_SIZE) ? 1 : 0);
		dev_dbg(dev, "init: %d arenas for %llu rawsize\n",
				btt->num_arenas, rawsize);

		ret = create_arenas(btt);
		if (ret) {
			dev_info(dev, "init: create_arenas: %d\n", ret);
			return NULL;
		}

		ret = btt_meta_init(btt);
		if (ret) {
			dev_err(dev, "init: error in meta_init: %d\n", ret);
			return NULL;
		}
	}

	ret = btt_blk_init(btt);
	if (ret) {
		dev_err(dev, "init: error in blk_init: %d\n", ret);
		return NULL;
	}

	btt_debugfs_init(btt);

	return btt;
}