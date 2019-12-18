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
 int /*<<< orphan*/  strndup_append_at (char**,int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  ta_free (char*) ; 
 int /*<<< orphan*/  ta_set_parent (char*,void*) ; 

char *ta_strndup(void *ta_parent, const char *str, size_t n)
{
    if (!str)
        return NULL;
    char *new = NULL;
    strndup_append_at(&new, 0, str, n);
    if (!ta_set_parent(new, ta_parent)) {
        ta_free(new);
        new = NULL;
    }
    return new;
}