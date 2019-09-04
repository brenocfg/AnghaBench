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
struct SmackMatches {unsigned int m_count; size_t* m_ids; } ;
struct SMACK {struct SmackMatches* m_match; } ;

/* Variables and functions */

__attribute__((used)) static unsigned
handle_match(    struct SMACK * smack,
                unsigned index,
                int (*callback_function)(size_t id, int index, void *callback_data),
                void *callback_data,
                unsigned state)
{
    unsigned i;
    struct SmackMatches *match = &smack->m_match[state];

    /*
     * Notify caller of all possible matches.
     */
    for (i=0; i<match->m_count; i++) {
        size_t id = match->m_ids[i];
        callback_function(id, index, callback_data);
    }

    return match->m_count;
}