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
typedef  int /*<<< orphan*/  transition_t ;
struct SmackMatches {int m_count; size_t* m_ids; } ;
struct SMACK {unsigned char* char_to_symbol; unsigned int row_shift; unsigned int m_match_limit; struct SmackMatches* m_match; int /*<<< orphan*/ * table; } ;

/* Variables and functions */
 size_t inner_match (unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/  const*,unsigned int*,unsigned int,unsigned int) ; 
 size_t inner_match_shift7 (unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/  const*,unsigned int*,unsigned int) ; 

size_t
smack_search_next(      struct SMACK *  smack,
                        unsigned *      current_state,
                        const void *    v_px,
                        unsigned *       offset,
                        unsigned        length
                        )
{
    const unsigned char *px = (const unsigned char*)v_px;
    unsigned row;
    register size_t i = *offset;
    const unsigned char *char_to_symbol = smack->char_to_symbol;
    const transition_t *table = smack->table;
    register unsigned row_shift = smack->row_shift;
    const struct SmackMatches *match = smack->m_match;
    unsigned current_matches = 0;
    size_t id = (size_t)-1;
    register unsigned match_limit = smack->m_match_limit;

    /* Get the row. This is encoded as the lower 24-bits of the state
     * variable */
    row = *current_state & 0xFFFFFF;

    /* See if there are current matches we are processing */
    current_matches = (*current_state)>>24;
 
    /* 'for all bytes in this block' */
    if (!current_matches) {
        /*if ((length-i) & 1)
            i += inner_match(px + i, 
                             length - i,
                             char_to_symbol,
                             table, 
                             &row, 
                             match_limit,
                             row_shift);
        if (row < match_limit && i < length)*/
        switch (row_shift) {
            case 7:
                i += inner_match_shift7(px + i, 
                                 length - i,
                                 char_to_symbol,
                                 table, 
                                 &row, 
                                 match_limit);
                break;
            default:
                i += inner_match(px + i, 
                                 length - i,
                                 char_to_symbol,
                                 table, 
                                 &row, 
                                 match_limit,
                                 row_shift);
                break;

        }

        //printf("*** row=%u, i=%u, limit=%u\n", row, i, match_limit);

        /* Test to see if we have one (or more) matches, and if so, call
         * the callback function */
        if (match[row].m_count) {
            i++; /* points to first byte after match */
            current_matches = match[row].m_count;
        }
    }

    *offset = (unsigned)i;

    /* If we broke early because we found a match, return that match */
    if (current_matches) {
        id = match[row].m_ids[current_matches-1];
        current_matches--;
    }

    *current_state = row | (current_matches<<24);
    return id;
}