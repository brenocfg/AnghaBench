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
struct log_group {TYPE_1__* ent; } ;
struct arena_info {int* log_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int log_seq (struct log_group*,int) ; 

__attribute__((used)) static int btt_log_get_old(struct arena_info *a, struct log_group *log)
{
	int idx0 = a->log_index[0];
	int idx1 = a->log_index[1];
	int old;

	/*
	 * the first ever time this is seen, the entry goes into [0]
	 * the next time, the following logic works out to put this
	 * (next) entry into [1]
	 */
	if (log_seq(log, idx0) == 0) {
		log->ent[idx0].seq = cpu_to_le32(1);
		return 0;
	}

	if (log_seq(log, idx0) == log_seq(log, idx1))
		return -EINVAL;
	if (log_seq(log, idx0) + log_seq(log, idx1) > 5)
		return -EINVAL;

	if (log_seq(log, idx0) < log_seq(log, idx1)) {
		if ((log_seq(log, idx1) - log_seq(log, idx0)) == 1)
			old = 0;
		else
			old = 1;
	} else {
		if ((log_seq(log, idx0) - log_seq(log, idx1)) == 1)
			old = 1;
		else
			old = 0;
	}

	return old;
}