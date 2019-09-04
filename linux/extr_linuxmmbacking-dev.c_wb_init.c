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
struct bdi_writeback {int /*<<< orphan*/  congested; int /*<<< orphan*/  completions; int /*<<< orphan*/ * stat; void* dirty_sleep; int /*<<< orphan*/  dwork; int /*<<< orphan*/  work_list; int /*<<< orphan*/  work_lock; void* avg_write_bandwidth; void* write_bandwidth; void* dirty_ratelimit; void* balanced_dirty_ratelimit; void* bw_time_stamp; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  b_dirty_time; int /*<<< orphan*/  b_more_io; int /*<<< orphan*/  b_io; int /*<<< orphan*/  b_dirty; void* last_old_flush; struct backing_dev_info* bdi; } ;
struct backing_dev_info {struct bdi_writeback wb; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 void* INIT_BW ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NR_WB_STAT_ITEMS ; 
 int /*<<< orphan*/  bdi_get (struct backing_dev_info*) ; 
 int /*<<< orphan*/  bdi_put (struct backing_dev_info*) ; 
 int /*<<< orphan*/  fprop_local_destroy_percpu (int /*<<< orphan*/ *) ; 
 int fprop_local_init_percpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  memset (struct bdi_writeback*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 int percpu_counter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_congested_get_create (struct backing_dev_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_congested_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_workfn ; 

__attribute__((used)) static int wb_init(struct bdi_writeback *wb, struct backing_dev_info *bdi,
		   int blkcg_id, gfp_t gfp)
{
	int i, err;

	memset(wb, 0, sizeof(*wb));

	if (wb != &bdi->wb)
		bdi_get(bdi);
	wb->bdi = bdi;
	wb->last_old_flush = jiffies;
	INIT_LIST_HEAD(&wb->b_dirty);
	INIT_LIST_HEAD(&wb->b_io);
	INIT_LIST_HEAD(&wb->b_more_io);
	INIT_LIST_HEAD(&wb->b_dirty_time);
	spin_lock_init(&wb->list_lock);

	wb->bw_time_stamp = jiffies;
	wb->balanced_dirty_ratelimit = INIT_BW;
	wb->dirty_ratelimit = INIT_BW;
	wb->write_bandwidth = INIT_BW;
	wb->avg_write_bandwidth = INIT_BW;

	spin_lock_init(&wb->work_lock);
	INIT_LIST_HEAD(&wb->work_list);
	INIT_DELAYED_WORK(&wb->dwork, wb_workfn);
	wb->dirty_sleep = jiffies;

	wb->congested = wb_congested_get_create(bdi, blkcg_id, gfp);
	if (!wb->congested) {
		err = -ENOMEM;
		goto out_put_bdi;
	}

	err = fprop_local_init_percpu(&wb->completions, gfp);
	if (err)
		goto out_put_cong;

	for (i = 0; i < NR_WB_STAT_ITEMS; i++) {
		err = percpu_counter_init(&wb->stat[i], 0, gfp);
		if (err)
			goto out_destroy_stat;
	}

	return 0;

out_destroy_stat:
	while (i--)
		percpu_counter_destroy(&wb->stat[i]);
	fprop_local_destroy_percpu(&wb->completions);
out_put_cong:
	wb_congested_put(wb->congested);
out_put_bdi:
	if (wb != &bdi->wb)
		bdi_put(bdi);
	return err;
}