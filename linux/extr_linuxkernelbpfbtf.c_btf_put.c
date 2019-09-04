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
struct btf {int /*<<< orphan*/  rcu; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  btf_free_id (struct btf*) ; 
 int /*<<< orphan*/  btf_free_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void btf_put(struct btf *btf)
{
	if (btf && refcount_dec_and_test(&btf->refcnt)) {
		btf_free_id(btf);
		call_rcu(&btf->rcu, btf_free_rcu);
	}
}