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
typedef  int u8 ;
struct qm_mr {scalar_t__ cmode; int ci; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int QM_MR_SIZE ; 
 int /*<<< orphan*/  QM_REG_MR_CI_CINH ; 
 scalar_t__ qm_mr_cci ; 
 int /*<<< orphan*/  qm_out (struct qm_portal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void qm_mr_cci_consume(struct qm_portal *portal, u8 num)
{
	struct qm_mr *mr = &portal->mr;

	DPAA_ASSERT(mr->cmode == qm_mr_cci);
	mr->ci = (mr->ci + num) & (QM_MR_SIZE - 1);
	qm_out(portal, QM_REG_MR_CI_CINH, mr->ci);
}