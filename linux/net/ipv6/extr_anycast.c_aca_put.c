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
struct ifacaddr6 {int /*<<< orphan*/  rcu; int /*<<< orphan*/  aca_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  aca_free_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aca_put(struct ifacaddr6 *ac)
{
	if (refcount_dec_and_test(&ac->aca_refcnt)) {
		call_rcu(&ac->rcu, aca_free_rcu);
	}
}