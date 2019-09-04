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
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_label_free (struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 

__attribute__((used)) static void label_free_or_put_new(struct aa_label *label, struct aa_label *new)
{
	if (label != new)
		/* need to free directly to break circular ref with proxy */
		aa_label_free(new);
	else
		aa_put_label(new);
}