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
 void const* OBJ_bsearch_ex_ (void const*,void const*,int,int,int (*) (void const*,void const*),int /*<<< orphan*/ ) ; 

const void *OBJ_bsearch_(const void *key, const void *base, int num, int size,
                         int (*cmp) (const void *, const void *))
{
    return OBJ_bsearch_ex_(key, base, num, size, cmp, 0);
}