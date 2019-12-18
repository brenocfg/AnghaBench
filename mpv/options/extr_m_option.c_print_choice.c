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
struct m_opt_choice_alternatives {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 struct m_opt_choice_alternatives* get_choice (int /*<<< orphan*/  const*,void const*,int*) ; 
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,int) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *print_choice(const m_option_t *opt, const void *val)
{
    int ival = 0;
    struct m_opt_choice_alternatives *alt = get_choice(opt, val, &ival);
    return alt ? talloc_strdup(NULL, alt->name)
               : talloc_asprintf(NULL, "%d", ival);
}