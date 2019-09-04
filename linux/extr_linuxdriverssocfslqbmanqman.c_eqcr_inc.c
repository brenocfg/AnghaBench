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
struct qm_eqcr_entry {int dummy; } ;
struct qm_eqcr {int /*<<< orphan*/  vbit; struct qm_eqcr_entry* cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  QM_EQCR_VERB_VBIT ; 
 struct qm_eqcr_entry* eqcr_carryclear (struct qm_eqcr_entry*) ; 

__attribute__((used)) static inline void eqcr_inc(struct qm_eqcr *eqcr)
{
	/* increment to the next EQCR pointer and handle overflow and 'vbit' */
	struct qm_eqcr_entry *partial = eqcr->cursor + 1;

	eqcr->cursor = eqcr_carryclear(partial);
	if (partial != eqcr->cursor)
		eqcr->vbit ^= QM_EQCR_VERB_VBIT;
}