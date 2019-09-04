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
struct dquot {int /*<<< orphan*/  dq_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQST_FREE_DQUOTS ; 
 int /*<<< orphan*/  dqstats_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void remove_free_dquot(struct dquot *dquot)
{
	if (list_empty(&dquot->dq_free))
		return;
	list_del_init(&dquot->dq_free);
	dqstats_dec(DQST_FREE_DQUOTS);
}