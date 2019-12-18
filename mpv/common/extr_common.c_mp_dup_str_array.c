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
 int /*<<< orphan*/  MP_TARRAY_APPEND (void*,char**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * talloc_strdup (void*,char*) ; 

char **mp_dup_str_array(void *tctx, char **s)
{
    char **r = NULL;
    int num_r = 0;
    for (int n = 0; s && s[n]; n++)
        MP_TARRAY_APPEND(tctx, r, num_r, talloc_strdup(tctx, s[n]));
    if (r)
        MP_TARRAY_APPEND(tctx, r, num_r, NULL);
    return r;
}