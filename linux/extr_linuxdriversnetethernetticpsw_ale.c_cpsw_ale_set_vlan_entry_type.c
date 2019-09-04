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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_TYPE_ADDR ; 
 int /*<<< orphan*/  ALE_TYPE_VLAN_ADDR ; 
 int ALE_VLAN ; 
 int /*<<< orphan*/  cpsw_ale_set_entry_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ale_set_vlan_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cpsw_ale_set_vlan_entry_type(u32 *ale_entry,
						int flags, u16 vid)
{
	if (flags & ALE_VLAN) {
		cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_VLAN_ADDR);
		cpsw_ale_set_vlan_id(ale_entry, vid);
	} else {
		cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_ADDR);
	}
}