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
struct key_tag {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct key_tag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

bool key_put_tag(struct key_tag *tag)
{
	if (refcount_dec_and_test(&tag->usage)) {
		kfree_rcu(tag, rcu);
		return true;
	}

	return false;
}