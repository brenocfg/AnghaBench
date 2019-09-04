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
struct aa_dfa {int /*<<< orphan*/ ** tables; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kfree (struct aa_dfa*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dfa_free(struct aa_dfa *dfa)
{
	if (dfa) {
		int i;

		for (i = 0; i < ARRAY_SIZE(dfa->tables); i++) {
			kvfree(dfa->tables[i]);
			dfa->tables[i] = NULL;
		}
		kfree(dfa);
	}
}