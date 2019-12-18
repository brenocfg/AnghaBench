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
struct aa_label {int /*<<< orphan*/  size; int /*<<< orphan*/  vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int vec_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int label_cmp(struct aa_label *a, struct aa_label *b)
{
	AA_BUG(!b);

	if (a == b)
		return 0;

	return vec_cmp(a->vec, a->size, b->vec, b->size);
}