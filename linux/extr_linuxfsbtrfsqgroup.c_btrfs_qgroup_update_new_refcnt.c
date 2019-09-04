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
typedef  scalar_t__ u64 ;
struct btrfs_qgroup {scalar_t__ new_refcnt; } ;

/* Variables and functions */

__attribute__((used)) static void btrfs_qgroup_update_new_refcnt(struct btrfs_qgroup *qg, u64 seq,
					   int mod)
{
	if (qg->new_refcnt < seq)
		qg->new_refcnt = seq;
	qg->new_refcnt += mod;
}