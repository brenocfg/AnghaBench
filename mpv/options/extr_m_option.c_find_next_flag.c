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
struct m_option {struct m_opt_choice_alternatives* priv; } ;
struct m_opt_choice_alternatives {char const* name; int value; } ;

/* Variables and functions */
 scalar_t__ av_popcount64 (int) ; 

__attribute__((used)) static const char *find_next_flag(const struct m_option *opt, int *val)
{
    struct m_opt_choice_alternatives *best = NULL;
    struct m_opt_choice_alternatives *alt;
    for (alt = opt->priv; alt->name; alt++) {
        if (alt->value && (alt->value & (*val)) == alt->value) {
            if (!best || av_popcount64(alt->value) > av_popcount64(best->value))
                best = alt;
        }
    }
    if (best) {
        *val = *val & ~(unsigned)best->value;
        return best->name;
    }
    *val = 0; // if there are still flags left, there's not much we can do
    return NULL;
}