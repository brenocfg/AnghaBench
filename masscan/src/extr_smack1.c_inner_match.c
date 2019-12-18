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

/* Variables and functions */

__attribute__((used)) static size_t
inner_match(    const unsigned char *px, 
                size_t length,
                const unsigned char *char_to_symbol,
                const transition_t *table, 
                unsigned *state, 
                unsigned match_limit,
                unsigned row_shift) 
{
    const unsigned char *px_start = px;
    const unsigned char *px_end = px + length;
    unsigned row = *state;
    
    for ( ; px<px_end; px++) {
        unsigned char column;
        
        /* Convert that character into a symbol. This compresses the table.
         * Even though there are 256 possible combinations for a byte, we
         * are probably using fewer than 32 individual characters in the
         * patterns we are looking for. This step allows us to create tables
         * that are only 32 elements wide, instead of 256 elements wide */
        column = char_to_symbol[*px];
        
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
        
        if (row >= match_limit)
            break;
        
    }

    *state = row;
    return px - px_start;
}