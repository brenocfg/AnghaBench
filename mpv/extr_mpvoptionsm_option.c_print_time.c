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
 scalar_t__ HAS_NOPTS (int /*<<< orphan*/  const*) ; 
 double MP_NOPTS_VALUE ; 
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,double) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char *print_time(const m_option_t *opt, const void *val)
{
    double pts = *(double *)val;
    if (pts == MP_NOPTS_VALUE && HAS_NOPTS(opt))
        return talloc_strdup(NULL, "no"); // symmetry with parsing
    return talloc_asprintf(NULL, "%f", pts);
}