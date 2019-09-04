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
struct SMACK {struct SMACK* table; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_intermediate_table (struct SMACK*) ; 
 int /*<<< orphan*/  destroy_matches_table (struct SMACK*) ; 
 int /*<<< orphan*/  destroy_pattern_table (struct SMACK*) ; 
 int /*<<< orphan*/  free (struct SMACK*) ; 

void
smack_destroy(struct SMACK *smack)
{
    destroy_intermediate_table(smack);
    destroy_matches_table(smack);
    destroy_pattern_table(smack);

    if (smack->table)
        free(smack->table);

    free(smack);
}