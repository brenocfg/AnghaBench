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
typedef  size_t transition_t ;
struct SmackMatches {char* DEBUG_name; scalar_t__ m_count; } ;
struct SMACK {unsigned char* char_to_symbol; size_t* table; unsigned int row_shift; struct SmackMatches* m_match; } ;
typedef  int /*<<< orphan*/  FOUND_CALLBACK ;

/* Variables and functions */
 unsigned int handle_match (struct SMACK*,unsigned int,int /*<<< orphan*/ ,void*,unsigned int) ; 
 scalar_t__ print_transitions ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned char,char*,char*) ; 

unsigned
smack_search(    struct SMACK * smack,
                const void *v_px,
                unsigned length,
                FOUND_CALLBACK cb_found,
                void *callback_data,
                unsigned *current_state)
{
    const unsigned char *px = (const unsigned char*)v_px;
    unsigned row;
    unsigned i;
    const unsigned char *char_to_symbol = smack->char_to_symbol;
    transition_t *table = smack->table;
    unsigned row_shift = smack->row_shift;
    unsigned found_count = 0;
    const struct SmackMatches *match = smack->m_match;

    /* Get the row. This is encoded as the lower 24-bits of the state
     * variable */
    row = *current_state & 0xFFFFFF;

    /* 'for all bytes in this block' */
    for (i=0; i<length; i++) {
        unsigned char column;
        unsigned char c;

        /* Get the next character of input */
        c = px[i];

        /* Convert that character into a symbol. This compresses the table.
         * Even though there are 256 possible combinations for a byte, we
         * are probably using fewer than 32 individual characters in the
         * patterns we are looking for. This step allows us to create tables
         * that are only 32 elements wide, instead of 256 elements wide */
        column = char_to_symbol[c];

        /*
         * If debugging, and the variable is set, then print out the
         * transition to the command line. This is a good way of visualizing
         * how they work.
         */
#ifdef DEBUG
        if (print_transitions) {
            printf("%s+%c = %s%s\n",
                    smack->m_match[row].DEBUG_name,
                    c,
                    smack->m_match[*(table + (row<<row_shift) + column)].DEBUG_name,
                    smack->m_match[*(table + (row<<row_shift) + column)].m_count?"$$":"");
            print_transitions--;
        }
#endif

        /*
         * STATE TRANSITION
         * Given the current row, lookup the symbol, and find the next row.
         * Logically, this is the following  calculation:
         *    row = table[row][column]
         * However, since row can have a variable width (depending on the
         * number of characters in a pattern), we have to do the calculation
         * manually.
         */
        row = *(table + (row<<row_shift) + column);

        /* Test to see if we have one (or more) matches, and if so, call
         * the callback function */
        if (match[row].m_count)
            found_count = handle_match(smack, i, cb_found, callback_data, row);
    }
    *current_state = row;
    return found_count;
}