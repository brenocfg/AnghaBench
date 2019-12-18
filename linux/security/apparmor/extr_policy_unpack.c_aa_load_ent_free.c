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
struct aa_load_ent {int /*<<< orphan*/  ns_name; int /*<<< orphan*/  new; int /*<<< orphan*/  old; int /*<<< orphan*/  rename; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_put_profile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct aa_load_ent*) ; 

void aa_load_ent_free(struct aa_load_ent *ent)
{
	if (ent) {
		aa_put_profile(ent->rename);
		aa_put_profile(ent->old);
		aa_put_profile(ent->new);
		kfree(ent->ns_name);
		kzfree(ent);
	}
}