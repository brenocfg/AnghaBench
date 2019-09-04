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
typedef  scalar_t__ u8 ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 scalar_t__ IWL_MVM_DQA_MAX_MGMT_QUEUE ; 
 scalar_t__ IWL_MVM_DQA_MIN_MGMT_QUEUE ; 

__attribute__((used)) static inline bool iwl_mvm_is_dqa_mgmt_queue(struct iwl_mvm *mvm, u8 queue)
{
	return (queue >= IWL_MVM_DQA_MIN_MGMT_QUEUE) &&
	       (queue <= IWL_MVM_DQA_MAX_MGMT_QUEUE);
}