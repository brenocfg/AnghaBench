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
typedef  int /*<<< orphan*/  u64 ;
struct cfs_rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rq_clock_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_of (struct cfs_rq*) ; 

__attribute__((used)) static inline u64 cfs_rq_clock_task(struct cfs_rq *cfs_rq)
{
	return rq_clock_task(rq_of(cfs_rq));
}