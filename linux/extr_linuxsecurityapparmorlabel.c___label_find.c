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
 struct aa_label* __vec_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct aa_label *__label_find(struct aa_label *label)
{
	AA_BUG(!label);

	return __vec_find(label->vec, label->size);
}