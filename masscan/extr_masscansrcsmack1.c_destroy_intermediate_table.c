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
struct SMACK {scalar_t__ m_state_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 

__attribute__((used)) static void
destroy_intermediate_table(struct SMACK *smack)
{
    if (smack->m_state_table) {
        free(smack->m_state_table);
        smack->m_state_table = 0;
    }
}