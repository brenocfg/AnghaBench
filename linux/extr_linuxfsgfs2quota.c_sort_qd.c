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
struct gfs2_quota_data {int /*<<< orphan*/  qd_id; } ;

/* Variables and functions */
 scalar_t__ qid_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sort_qd(const void *a, const void *b)
{
	const struct gfs2_quota_data *qd_a = *(const struct gfs2_quota_data **)a;
	const struct gfs2_quota_data *qd_b = *(const struct gfs2_quota_data **)b;

	if (qid_lt(qd_a->qd_id, qd_b->qd_id))
		return -1;
	if (qid_lt(qd_b->qd_id, qd_a->qd_id))
		return 1;
	return 0;
}