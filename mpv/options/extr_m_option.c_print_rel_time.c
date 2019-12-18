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
struct m_rel_time {int type; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
#define  REL_TIME_ABSOLUTE 131 
#define  REL_TIME_CHAPTER 130 
#define  REL_TIME_PERCENT 129 
#define  REL_TIME_RELATIVE 128 
 int /*<<< orphan*/  fabs (int /*<<< orphan*/ ) ; 
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char *print_rel_time(const m_option_t *opt, const void *val)
{
    const struct m_rel_time *t = val;
    switch(t->type) {
    case REL_TIME_ABSOLUTE:
        return talloc_asprintf(NULL, "%g", t->pos);
    case REL_TIME_RELATIVE:
        return talloc_asprintf(NULL, "%s%g",
            (t->pos >= 0) ? "+" : "-", fabs(t->pos));
    case REL_TIME_CHAPTER:
        return talloc_asprintf(NULL, "#%g", t->pos);
    case REL_TIME_PERCENT:
        return talloc_asprintf(NULL, "%g%%", t->pos);
    }
    return talloc_strdup(NULL, "none");
}