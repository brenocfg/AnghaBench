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
inner_match_shift7(    const unsigned char *px, 
            size_t length,
            const unsigned char *char_to_symbol,
            const transition_t *table, 
            unsigned *state, 
            unsigned match_limit) 
{
    const unsigned char *px_start = px;
    const unsigned char *px_end = px + length;
    unsigned row = *state;
    
    for ( ; px<px_end; px++) {
        unsigned char column;
        column = char_to_symbol[*px];
        row = *(table + (row<<7) + column);
        if (row >= match_limit)
            break;
    }
    
    *state = row;
    return px - px_start;
}