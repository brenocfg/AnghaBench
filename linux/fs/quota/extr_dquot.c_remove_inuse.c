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
struct dquot {int /*<<< orphan*/  dq_inuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQST_ALLOC_DQUOTS ; 
 int /*<<< orphan*/  dqstats_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void remove_inuse(struct dquot *dquot)
{
	dqstats_dec(DQST_ALLOC_DQUOTS);
	list_del(&dquot->dq_inuse);
}