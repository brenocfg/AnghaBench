#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aa_dfa {TYPE_1__** tables; } ;
struct TYPE_2__ {int td_lolen; } ;

/* Variables and functions */
 size_t YYTD_ID_ACCEPT ; 
 int /*<<< orphan*/  dfa_other_xindex (struct aa_dfa*,int) ; 
 int /*<<< orphan*/  dfa_user_xindex (struct aa_dfa*,int) ; 
 int /*<<< orphan*/  verify_xindex (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool verify_dfa_xindex(struct aa_dfa *dfa, int table_size)
{
	int i;
	for (i = 0; i < dfa->tables[YYTD_ID_ACCEPT]->td_lolen; i++) {
		if (!verify_xindex(dfa_user_xindex(dfa, i), table_size))
			return 0;
		if (!verify_xindex(dfa_other_xindex(dfa, i), table_size))
			return 0;
	}
	return 1;
}