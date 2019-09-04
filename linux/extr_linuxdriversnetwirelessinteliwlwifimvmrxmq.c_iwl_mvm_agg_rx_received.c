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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm_baid_data {unsigned long timeout; unsigned long last_rx; } ;
struct iwl_mvm {int /*<<< orphan*/ * baid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_mvm*,char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ TU_TO_JIFFIES (unsigned long) ; 
 unsigned long jiffies ; 
 struct iwl_mvm_baid_data* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ time_before (scalar_t__,unsigned long) ; 

__attribute__((used)) static void iwl_mvm_agg_rx_received(struct iwl_mvm *mvm,
				    u32 reorder_data, u8 baid)
{
	unsigned long now = jiffies;
	unsigned long timeout;
	struct iwl_mvm_baid_data *data;

	rcu_read_lock();

	data = rcu_dereference(mvm->baid_map[baid]);
	if (!data) {
		IWL_DEBUG_RX(mvm,
			     "Got valid BAID but no baid allocated, bypass the re-ordering buffer. Baid %d reorder 0x%x\n",
			      baid, reorder_data);
		goto out;
	}

	if (!data->timeout)
		goto out;

	timeout = data->timeout;
	/*
	 * Do not update last rx all the time to avoid cache bouncing
	 * between the rx queues.
	 * Update it every timeout. Worst case is the session will
	 * expire after ~ 2 * timeout, which doesn't matter that much.
	 */
	if (time_before(data->last_rx + TU_TO_JIFFIES(timeout), now))
		/* Update is atomic */
		data->last_rx = now;

out:
	rcu_read_unlock();
}