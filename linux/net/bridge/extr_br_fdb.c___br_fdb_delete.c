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
typedef  int /*<<< orphan*/  u16 ;
struct net_bridge_port {int dummy; } ;
struct net_bridge {int /*<<< orphan*/  hash_lock; } ;

/* Variables and functions */
 int fdb_delete_by_addr_and_port (struct net_bridge*,struct net_bridge_port const*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __br_fdb_delete(struct net_bridge *br,
			   const struct net_bridge_port *p,
			   const unsigned char *addr, u16 vid)
{
	int err;

	spin_lock_bh(&br->hash_lock);
	err = fdb_delete_by_addr_and_port(br, p, addr, vid);
	spin_unlock_bh(&br->hash_lock);

	return err;
}