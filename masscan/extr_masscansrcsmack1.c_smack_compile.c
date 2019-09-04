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
struct SmackPattern {scalar_t__ is_anchor_end; scalar_t__ is_anchor_begin; scalar_t__ pattern_length; } ;
struct SMACK {int m_state_max; scalar_t__ is_anchor_begin; struct SmackPattern** m_pattern_list; scalar_t__ m_pattern_count; int /*<<< orphan*/ * char_to_symbol; scalar_t__ is_nocase; scalar_t__ is_anchor_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_STATE ; 
 int /*<<< orphan*/  CHAR_ANCHOR_END ; 
 int /*<<< orphan*/  CHAR_ANCHOR_START ; 
 int /*<<< orphan*/  UNANCHORED_STATE ; 
 int /*<<< orphan*/  create_intermediate_table (struct SMACK*,int) ; 
 int /*<<< orphan*/  create_matches_table (struct SMACK*,int) ; 
 int /*<<< orphan*/  destroy_intermediate_table (struct SMACK*) ; 
 int /*<<< orphan*/  destroy_pattern_table (struct SMACK*) ; 
 int /*<<< orphan*/  smack_add_symbol (struct SMACK*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smack_fixup_wildcards (struct SMACK*) ; 
 int /*<<< orphan*/  smack_stage0_compile_prefixes (struct SMACK*) ; 
 int /*<<< orphan*/  smack_stage1_generate_fails (struct SMACK*) ; 
 int /*<<< orphan*/  smack_stage2_link_fails (struct SMACK*) ; 
 int /*<<< orphan*/  smack_stage3_sort (struct SMACK*) ; 
 int /*<<< orphan*/  smack_stage4_make_final_table (struct SMACK*) ; 
 int /*<<< orphan*/  swap_rows (struct SMACK*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t tolower (unsigned int) ; 

void
smack_compile(struct SMACK *smack)
{
    unsigned i;

    /*
     * Fix up the symbol table to handle "anchors" and "nocase" conditions.
     */
    if (smack->is_anchor_begin)
        smack_add_symbol(smack, CHAR_ANCHOR_START);
    if (smack->is_anchor_end)
        smack_add_symbol(smack, CHAR_ANCHOR_END);
    if (smack->is_nocase) {
        for (i='A'; i<='Z'; i++) {
            smack->char_to_symbol[i] = smack->char_to_symbol[tolower(i)];
        }
    }


    /*
     * Calculate the maximum possible number of states. This will be somewhat
     * larger than the number of states we'll actually use because there can
     * be overlaps
     */
    smack->m_state_max = 1;
    for (i=0; i<(int)smack->m_pattern_count; i++) {
        struct SmackPattern *pat = smack->m_pattern_list[i];

        smack->m_state_max += pat->pattern_length;
        smack->m_state_max += pat->is_anchor_begin;
        smack->m_state_max += pat->is_anchor_end;
    }

    /*
     * Allocate a state-table that can hold that number of states
     */
    create_intermediate_table(smack, smack->m_state_max);
    create_matches_table(smack, smack->m_state_max);


    /*
     * Go through the various compilation stages
     */
    smack_stage0_compile_prefixes(smack);
    smack_stage1_generate_fails(smack);
    smack_stage2_link_fails(smack);


    /* If we have an anchor pattern, then swap
     * the first two states. */
    if (smack->is_anchor_begin) {
        swap_rows(smack, BASE_STATE, UNANCHORED_STATE);
    }

    /* prettify table for debugging */
    smack_stage3_sort(smack);

    /*
     * Build the final table we use for evaluation
     */
    smack_stage4_make_final_table(smack);
    
    /*
     * Fixup the wildcard states
     */
    smack_fixup_wildcards(smack);

    /*
     * Get rid of the original pattern tables, since we no longer need them.
     * However, if this is a debug build, keep the tables around to make
     * debugging easier
     */
#ifndef DEBUG
    destroy_pattern_table(smack);
    destroy_intermediate_table(smack);
#endif
}