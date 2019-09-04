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
struct SmackMatches {size_t* m_ids; } ;
struct SMACK {struct SmackMatches* m_match; } ;

/* Variables and functions */
 size_t SMACK_NOT_FOUND ; 

size_t
smack_next_match(struct SMACK *smack, unsigned *current_state)
{
    unsigned row, current_matches;
    size_t id = SMACK_NOT_FOUND;

    /* split the state variable */
    row = *current_state & 0xFFFFFF;
    current_matches = (*current_state)>>24;

    /* If we broke early because we found a match, return that match */
    if (current_matches) {
        const struct SmackMatches *match = smack->m_match;
        id = match[row].m_ids[current_matches-1];
        current_matches--;
    }

    /* Recombine the state */
    *current_state = row | (current_matches<<24);

    return id;
}