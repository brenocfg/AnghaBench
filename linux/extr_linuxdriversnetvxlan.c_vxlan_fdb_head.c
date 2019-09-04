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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int flags; } ;
struct vxlan_dev {struct hlist_head* fdb_head; TYPE_1__ cfg; } ;
struct hlist_head {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int VXLAN_F_COLLECT_METADATA ; 
 size_t eth_hash (int /*<<< orphan*/  const*) ; 
 size_t eth_vni_hash (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hlist_head *vxlan_fdb_head(struct vxlan_dev *vxlan,
						const u8 *mac, __be32 vni)
{
	if (vxlan->cfg.flags & VXLAN_F_COLLECT_METADATA)
		return &vxlan->fdb_head[eth_vni_hash(mac, vni)];
	else
		return &vxlan->fdb_head[eth_hash(mac)];
}