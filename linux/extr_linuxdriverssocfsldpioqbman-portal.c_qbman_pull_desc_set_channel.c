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
typedef  int /*<<< orphan*/  u32 ;
struct qbman_pull_desc {int verb; int /*<<< orphan*/  dq_src; } ;
typedef  enum qbman_pull_type_e { ____Placeholder_qbman_pull_type_e } qbman_pull_type_e ;

/* Variables and functions */
 int QB_VDQCR_VERB_DCT_SHIFT ; 
 int QB_VDQCR_VERB_DT_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int qb_pull_dt_channel ; 

void qbman_pull_desc_set_channel(struct qbman_pull_desc *d, u32 chid,
				 enum qbman_pull_type_e dct)
{
	d->verb |= dct << QB_VDQCR_VERB_DCT_SHIFT;
	d->verb |= qb_pull_dt_channel << QB_VDQCR_VERB_DT_SHIFT;
	d->dq_src = cpu_to_le32(chid);
}