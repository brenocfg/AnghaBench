#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ name; } ;
struct filter_kernel {TYPE_1__ f; } ;

/* Variables and functions */
 struct filter_kernel* mp_filter_kernels ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

const struct filter_kernel *mp_find_filter_kernel(const char *name)
{
    if (!name)
        return NULL;
    for (const struct filter_kernel *k = mp_filter_kernels; k->f.name; k++) {
        if (strcmp(k->f.name, name) == 0)
            return k;
    }
    return NULL;
}