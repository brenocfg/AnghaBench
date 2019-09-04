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
typedef  int u32 ;

/* Variables and functions */
 int DPAA_GENALLOC_OFF ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  qm_qpalloc ; 
 int qpool_cleanup (int) ; 

int qman_release_pool(u32 qp)
{
	int ret;

	ret = qpool_cleanup(qp);
	if (ret) {
		pr_debug("CHID %d leaked\n", qp);
		return ret;
	}

	gen_pool_free(qm_qpalloc, qp | DPAA_GENALLOC_OFF, 1);
	return 0;
}