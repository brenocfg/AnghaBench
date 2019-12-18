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
struct ipc_ids {int max_idx; int last_idx; int next_id; int /*<<< orphan*/  ipcs_idr; int /*<<< orphan*/  key_ht; int /*<<< orphan*/  rwsem; scalar_t__ seq; scalar_t__ in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_kht_params ; 
 int /*<<< orphan*/  rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ipc_init_ids(struct ipc_ids *ids)
{
	ids->in_use = 0;
	ids->seq = 0;
	init_rwsem(&ids->rwsem);
	rhashtable_init(&ids->key_ht, &ipc_kht_params);
	idr_init(&ids->ipcs_idr);
	ids->max_idx = -1;
	ids->last_idx = -1;
#ifdef CONFIG_CHECKPOINT_RESTORE
	ids->next_id = -1;
#endif
}