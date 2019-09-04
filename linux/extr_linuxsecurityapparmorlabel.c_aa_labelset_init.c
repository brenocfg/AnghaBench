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
struct aa_labelset {int /*<<< orphan*/  root; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

void aa_labelset_init(struct aa_labelset *ls)
{
	AA_BUG(!ls);

	rwlock_init(&ls->lock);
	ls->root = RB_ROOT;
}