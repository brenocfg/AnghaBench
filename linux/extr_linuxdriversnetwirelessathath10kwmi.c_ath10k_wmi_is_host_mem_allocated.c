#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct wlan_host_mem_req {int /*<<< orphan*/  num_unit_info; int /*<<< orphan*/  unit_size; int /*<<< orphan*/  num_units; int /*<<< orphan*/  req_id; } ;
struct TYPE_4__ {int num_mem_chunks; TYPE_1__* mem_chunks; } ;
struct ath10k {int num_active_peers; int max_num_peers; int max_num_vdevs; TYPE_2__ wmi; } ;
struct TYPE_3__ {int req_id; int len; } ;

/* Variables and functions */
 int NUM_UNITS_IS_NUM_ACTIVE_PEERS ; 
 int NUM_UNITS_IS_NUM_PEERS ; 
 int NUM_UNITS_IS_NUM_VDEVS ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int round_up (int,int) ; 

__attribute__((used)) static bool
ath10k_wmi_is_host_mem_allocated(struct ath10k *ar,
				 const struct wlan_host_mem_req **mem_reqs,
				 u32 num_mem_reqs)
{
	u32 req_id, num_units, unit_size, num_unit_info;
	u32 pool_size;
	int i, j;
	bool found;

	if (ar->wmi.num_mem_chunks != num_mem_reqs)
		return false;

	for (i = 0; i < num_mem_reqs; ++i) {
		req_id = __le32_to_cpu(mem_reqs[i]->req_id);
		num_units = __le32_to_cpu(mem_reqs[i]->num_units);
		unit_size = __le32_to_cpu(mem_reqs[i]->unit_size);
		num_unit_info = __le32_to_cpu(mem_reqs[i]->num_unit_info);

		if (num_unit_info & NUM_UNITS_IS_NUM_ACTIVE_PEERS) {
			if (ar->num_active_peers)
				num_units = ar->num_active_peers + 1;
			else
				num_units = ar->max_num_peers + 1;
		} else if (num_unit_info & NUM_UNITS_IS_NUM_PEERS) {
			num_units = ar->max_num_peers + 1;
		} else if (num_unit_info & NUM_UNITS_IS_NUM_VDEVS) {
			num_units = ar->max_num_vdevs + 1;
		}

		found = false;
		for (j = 0; j < ar->wmi.num_mem_chunks; j++) {
			if (ar->wmi.mem_chunks[j].req_id == req_id) {
				pool_size = num_units * round_up(unit_size, 4);
				if (ar->wmi.mem_chunks[j].len == pool_size) {
					found = true;
					break;
				}
			}
		}
		if (!found)
			return false;
	}

	return true;
}