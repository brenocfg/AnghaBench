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
struct m_option {int flags; int /*<<< orphan*/  max; int /*<<< orphan*/  min; struct m_opt_choice_alternatives* priv; int /*<<< orphan*/ * type; } ;
struct m_opt_choice_alternatives {int /*<<< orphan*/  value; scalar_t__ name; } ;

/* Variables and functions */
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int INT_MAX ; 
 int INT_MIN ; 
 int M_OPT_MAX ; 
 int M_OPT_MIN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  m_option_type_choice ; 

__attribute__((used)) static void choice_get_min_max(const struct m_option *opt, int *min, int *max)
{
    assert(opt->type == &m_option_type_choice);
    *min = INT_MAX;
    *max = INT_MIN;
    for (struct m_opt_choice_alternatives *alt = opt->priv; alt->name; alt++) {
        *min = FFMIN(*min, alt->value);
        *max = FFMAX(*max, alt->value);
    }
    if ((opt->flags & M_OPT_MIN) && (opt->flags & M_OPT_MAX)) {
        *min = FFMIN(*min, opt->min);
        *max = FFMAX(*max, opt->max);
    }
}