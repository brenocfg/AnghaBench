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
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_read_mem (struct iwl_trans*,int,int*,int) ; 

__attribute__((used)) static inline u32 iwl_trans_read_mem32(struct iwl_trans *trans, u32 addr)
{
	u32 value;

	if (WARN_ON(iwl_trans_read_mem(trans, addr, &value, 1)))
		return 0xa5a5a5a5;

	return value;
}