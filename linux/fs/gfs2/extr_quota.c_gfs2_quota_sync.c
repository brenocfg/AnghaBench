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
struct super_block {struct gfs2_sbd* s_fs_info; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_quota_sync_mutex; scalar_t__ sd_quota_sync_gen; } ;
struct gfs2_quota_data {scalar_t__ qd_sync_gen; } ;
struct gfs2_holder {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int do_sync (unsigned int,struct gfs2_quota_data**) ; 
 struct gfs2_quota_data** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gfs2_quota_data**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qd_fish (struct gfs2_sbd*,struct gfs2_quota_data**) ; 
 int /*<<< orphan*/  qd_unlock (struct gfs2_quota_data*) ; 

int gfs2_quota_sync(struct super_block *sb, int type)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;
	struct gfs2_quota_data **qda;
	unsigned int max_qd = PAGE_SIZE/sizeof(struct gfs2_holder);
	unsigned int num_qd;
	unsigned int x;
	int error = 0;

	qda = kcalloc(max_qd, sizeof(struct gfs2_quota_data *), GFP_KERNEL);
	if (!qda)
		return -ENOMEM;

	mutex_lock(&sdp->sd_quota_sync_mutex);
	sdp->sd_quota_sync_gen++;

	do {
		num_qd = 0;

		for (;;) {
			error = qd_fish(sdp, qda + num_qd);
			if (error || !qda[num_qd])
				break;
			if (++num_qd == max_qd)
				break;
		}

		if (num_qd) {
			if (!error)
				error = do_sync(num_qd, qda);
			if (!error)
				for (x = 0; x < num_qd; x++)
					qda[x]->qd_sync_gen =
						sdp->sd_quota_sync_gen;

			for (x = 0; x < num_qd; x++)
				qd_unlock(qda[x]);
		}
	} while (!error && num_qd == max_qd);

	mutex_unlock(&sdp->sd_quota_sync_mutex);
	kfree(qda);

	return error;
}