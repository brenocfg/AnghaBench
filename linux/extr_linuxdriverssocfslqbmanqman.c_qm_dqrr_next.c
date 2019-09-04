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
typedef  int /*<<< orphan*/  u8 ;
struct qm_dqrr {int /*<<< orphan*/  fill; int /*<<< orphan*/  cursor; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dqrr_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 qm_dqrr_next(struct qm_portal *portal)
{
	struct qm_dqrr *dqrr = &portal->dqrr;

	DPAA_ASSERT(dqrr->fill);
	dqrr->cursor = dqrr_inc(dqrr->cursor);
	return --dqrr->fill;
}