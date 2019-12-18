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
struct aa_file_rules {int /*<<< orphan*/  trans; int /*<<< orphan*/  dfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_free_domain_entries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aa_put_dfa (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void aa_free_file_rules(struct aa_file_rules *rules)
{
	aa_put_dfa(rules->dfa);
	aa_free_domain_entries(&rules->trans);
}