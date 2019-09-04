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
union bm_mc_result {int verb; } ;
typedef  int /*<<< orphan*/  u32 ;
struct bman_portal {int /*<<< orphan*/  p; } ;
struct bm_mc_command {int /*<<< orphan*/  bpid; } ;

/* Variables and functions */
 int BM_MCC_VERB_CMD_ACQUIRE ; 
 int BM_MCR_VERB_ACQUIRE_BUFCOUNT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  bm_mc_commit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bm_mc_result_timeout (int /*<<< orphan*/ *,union bm_mc_result**) ; 
 struct bm_mc_command* bm_mc_start (int /*<<< orphan*/ *) ; 
 struct bman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  put_affine_portal () ; 

__attribute__((used)) static int bm_shutdown_pool(u32 bpid)
{
	struct bm_mc_command *bm_cmd;
	union bm_mc_result *bm_res;

	while (1) {
		struct bman_portal *p = get_affine_portal();
		/* Acquire buffers until empty */
		bm_cmd = bm_mc_start(&p->p);
		bm_cmd->bpid = bpid;
		bm_mc_commit(&p->p, BM_MCC_VERB_CMD_ACQUIRE | 1);
		if (!bm_mc_result_timeout(&p->p, &bm_res)) {
			put_affine_portal();
			pr_crit("BMan Acquire Command timedout\n");
			return -ETIMEDOUT;
		}
		if (!(bm_res->verb & BM_MCR_VERB_ACQUIRE_BUFCOUNT)) {
			put_affine_portal();
			/* Pool is empty */
			return 0;
		}
		put_affine_portal();
	}

	return 0;
}