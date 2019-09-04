#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rcu_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cb_barrier ) () ;int /*<<< orphan*/  (* call ) (struct rcu_head*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array3_size (int,int,int) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ cbflood_inter_holdoff ; 
 scalar_t__ cbflood_intra_holdoff ; 
 int cbflood_n_burst ; 
 int cbflood_n_per_burst ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  n_cbfloods ; 
 int /*<<< orphan*/  rcu_torture_cbflood_cb ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (scalar_t__) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rcu_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stutter_wait (char*) ; 
 int /*<<< orphan*/  torture_kthread_stopping (char*) ; 
 int /*<<< orphan*/  torture_must_stop () ; 
 int /*<<< orphan*/  vfree (struct rcu_head*) ; 
 struct rcu_head* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rcu_torture_cbflood(void *arg)
{
	int err = 1;
	int i;
	int j;
	struct rcu_head *rhp;

	if (cbflood_n_per_burst > 0 &&
	    cbflood_inter_holdoff > 0 &&
	    cbflood_intra_holdoff > 0 &&
	    cur_ops->call &&
	    cur_ops->cb_barrier) {
		rhp = vmalloc(array3_size(cbflood_n_burst,
					  cbflood_n_per_burst,
					  sizeof(*rhp)));
		err = !rhp;
	}
	if (err) {
		VERBOSE_TOROUT_STRING("rcu_torture_cbflood disabled: Bad args or OOM");
		goto wait_for_stop;
	}
	VERBOSE_TOROUT_STRING("rcu_torture_cbflood task started");
	do {
		schedule_timeout_interruptible(cbflood_inter_holdoff);
		atomic_long_inc(&n_cbfloods);
		WARN_ON(signal_pending(current));
		for (i = 0; i < cbflood_n_burst; i++) {
			for (j = 0; j < cbflood_n_per_burst; j++) {
				cur_ops->call(&rhp[i * cbflood_n_per_burst + j],
					      rcu_torture_cbflood_cb);
			}
			schedule_timeout_interruptible(cbflood_intra_holdoff);
			WARN_ON(signal_pending(current));
		}
		cur_ops->cb_barrier();
		stutter_wait("rcu_torture_cbflood");
	} while (!torture_must_stop());
	vfree(rhp);
wait_for_stop:
	torture_kthread_stopping("rcu_torture_cbflood");
	return 0;
}