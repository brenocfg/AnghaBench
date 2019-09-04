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
 int /*<<< orphan*/  bm_bpalloc ; 
 int bm_shutdown_pool (int) ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int bm_release_bpid(u32 bpid)
{
	int ret;

	ret = bm_shutdown_pool(bpid);
	if (ret) {
		pr_debug("BPID %d leaked\n", bpid);
		return ret;
	}

	gen_pool_free(bm_bpalloc, bpid | DPAA_GENALLOC_OFF, 1);
	return 0;
}