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
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,int const) ; 
 char* talloc_asprintf_append (char*,char*,int const) ; 

__attribute__((used)) static char *print_intpair(const m_option_t *opt, const void *val)
{
    const int *p = val;
    char *res = talloc_asprintf(NULL, "%d", p[0]);
    if (p[1] != -1)
        res = talloc_asprintf_append(res, "-%d", p[1]);
    return res;
}