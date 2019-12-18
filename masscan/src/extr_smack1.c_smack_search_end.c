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
typedef  unsigned int transition_t ;
struct SmackMatches {scalar_t__ m_count; } ;
struct SMACK {unsigned int* table; unsigned int row_shift; unsigned int* char_to_symbol; struct SmackMatches* m_match; } ;
typedef  int /*<<< orphan*/  FOUND_CALLBACK ;

/* Variables and functions */
 size_t CHAR_ANCHOR_END ; 
 unsigned int handle_match (struct SMACK*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int) ; 

unsigned
smack_search_end(       struct SMACK *  smack,
                        FOUND_CALLBACK  cb_found,
                        void *          callback_data,
                        unsigned *      current_state)
{
    unsigned found_count = 0;
    transition_t *table = smack->table;
    unsigned row_shift = smack->row_shift;
    unsigned row = *current_state;
    const struct SmackMatches *match = smack->m_match;
    unsigned column = smack->char_to_symbol[CHAR_ANCHOR_END];

    /*
     * This is the same logic as for "smack_search()", except there is
     * only one byte of input -- the virtual character ($) that represents
     * the anchor at the end of some patterns.
     */
    row = *(table + (row<<row_shift) + column);
    if (match[row].m_count)
        found_count = handle_match(smack, 0, cb_found, callback_data, row);

    *current_state = row;
    return found_count;
}