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
struct aa_profile {int dummy; } ;
struct aa_labelset {int /*<<< orphan*/  lock; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 struct aa_label* __vec_find (struct aa_profile**,int) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct aa_labelset* vec_labelset (struct aa_profile**,int) ; 

__attribute__((used)) static struct aa_label *vec_find(struct aa_profile **vec, int n)
{
	struct aa_labelset *ls;
	struct aa_label *label;
	unsigned long flags;

	AA_BUG(!vec);
	AA_BUG(!*vec);
	AA_BUG(n <= 0);

	ls = vec_labelset(vec, n);
	read_lock_irqsave(&ls->lock, flags);
	label = __vec_find(vec, n);
	read_unlock_irqrestore(&ls->lock, flags);

	return label;
}