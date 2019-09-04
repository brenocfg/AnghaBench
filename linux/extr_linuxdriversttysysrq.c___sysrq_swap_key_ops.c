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
struct sysrq_key_op {int dummy; } ;

/* Variables and functions */
 struct sysrq_key_op* __sysrq_get_key_op (int) ; 
 int /*<<< orphan*/  __sysrq_put_key_op (int,struct sysrq_key_op*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  sysrq_key_table_lock ; 

__attribute__((used)) static int __sysrq_swap_key_ops(int key, struct sysrq_key_op *insert_op_p,
                                struct sysrq_key_op *remove_op_p)
{
	int retval;

	spin_lock(&sysrq_key_table_lock);
	if (__sysrq_get_key_op(key) == remove_op_p) {
		__sysrq_put_key_op(key, insert_op_p);
		retval = 0;
	} else {
		retval = -1;
	}
	spin_unlock(&sysrq_key_table_lock);

	/*
	 * A concurrent __handle_sysrq either got the old op or the new op.
	 * Wait for it to go away before returning, so the code for an old
	 * op is not freed (eg. on module unload) while it is in use.
	 */
	synchronize_rcu();

	return retval;
}