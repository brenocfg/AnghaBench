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

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 char const* talloc_asprintf (void*,char*,char const*,char const*) ; 

__attribute__((used)) static const char *concat_name(void *ta_parent, const char *a, const char *b)
{
    assert(a);
    assert(b);
    if (!a[0])
        return b;
    if (!b[0])
        return a;
    return talloc_asprintf(ta_parent, "%s-%s", a, b);
}