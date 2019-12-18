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
struct cfs_rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfs_rq_tg_path (struct cfs_rq*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

char *sched_trace_cfs_rq_path(struct cfs_rq *cfs_rq, char *str, int len)
{
	if (!cfs_rq) {
		if (str)
			strlcpy(str, "(null)", len);
		else
			return NULL;
	}

	cfs_rq_tg_path(cfs_rq, str, len);
	return str;
}