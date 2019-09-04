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
struct aa_dfa {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_dfa_free_kref ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void aa_put_dfa(struct aa_dfa *dfa)
{
	if (dfa)
		kref_put(&dfa->count, aa_dfa_free_kref);
}