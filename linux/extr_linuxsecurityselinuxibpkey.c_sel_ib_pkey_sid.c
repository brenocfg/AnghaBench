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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  sid; } ;
struct sel_ib_pkey {TYPE_1__ psec; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sel_ib_pkey* sel_ib_pkey_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sel_ib_pkey_sid_slow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sel_ib_pkey_sid(u64 subnet_prefix, u16 pkey_num, u32 *sid)
{
	struct sel_ib_pkey *pkey;

	rcu_read_lock();
	pkey = sel_ib_pkey_find(subnet_prefix, pkey_num);
	if (pkey) {
		*sid = pkey->psec.sid;
		rcu_read_unlock();
		return 0;
	}
	rcu_read_unlock();

	return sel_ib_pkey_sid_slow(subnet_prefix, pkey_num, sid);
}