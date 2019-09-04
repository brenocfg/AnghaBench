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
struct qman_portal {int dummy; } ;
struct qman_fq {int dummy; } ;
struct qm_dqrr_entry {int /*<<< orphan*/  fd; } ;
struct hp_handler {int /*<<< orphan*/  tx; } ;
typedef  enum qman_cb_dqrr_result { ____Placeholder_qman_cb_dqrr_result } qman_cb_dqrr_result ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 scalar_t__ process_frame_data (struct hp_handler*,int /*<<< orphan*/ *) ; 
 int qman_cb_dqrr_consume ; 
 scalar_t__ qman_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum qman_cb_dqrr_result normal_dqrr(struct qman_portal *portal,
					    struct qman_fq *fq,
					    const struct qm_dqrr_entry *dqrr)
{
	struct hp_handler *handler = (struct hp_handler *)fq;

	if (process_frame_data(handler, &dqrr->fd)) {
		WARN_ON(1);
		goto skip;
	}
	if (qman_enqueue(&handler->tx, &dqrr->fd)) {
		pr_crit("qman_enqueue() failed");
		WARN_ON(1);
	}
skip:
	return qman_cb_dqrr_consume;
}