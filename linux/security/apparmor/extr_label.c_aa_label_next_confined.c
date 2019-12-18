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
struct aa_label {int size; int /*<<< orphan*/ * vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  profile_unconfined (int /*<<< orphan*/ ) ; 

int aa_label_next_confined(struct aa_label *label, int i)
{
	AA_BUG(!label);
	AA_BUG(i < 0);

	for (; i < label->size; i++) {
		if (!profile_unconfined(label->vec[i]))
			return i;
	}

	return i;
}