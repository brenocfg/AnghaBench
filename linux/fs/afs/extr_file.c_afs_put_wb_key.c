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
struct afs_wb_key {int /*<<< orphan*/  key; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct afs_wb_key*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void afs_put_wb_key(struct afs_wb_key *wbk)
{
	if (refcount_dec_and_test(&wbk->usage)) {
		key_put(wbk->key);
		kfree(wbk);
	}
}