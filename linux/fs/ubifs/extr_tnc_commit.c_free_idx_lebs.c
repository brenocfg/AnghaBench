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
struct ubifs_info {int /*<<< orphan*/ * ilebs; } ;

/* Variables and functions */
 int free_unused_idx_lebs (struct ubifs_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int free_idx_lebs(struct ubifs_info *c)
{
	int err;

	err = free_unused_idx_lebs(c);
	kfree(c->ilebs);
	c->ilebs = NULL;
	return err;
}