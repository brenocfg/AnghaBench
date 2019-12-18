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
struct TYPE_2__ {char const* name; } ;
struct filter_kernel {TYPE_1__ f; int /*<<< orphan*/  polar; } ;

/* Variables and functions */
 char** fixed_scale_filters ; 
 char** fixed_tscale_filters ; 
 struct filter_kernel* mp_find_filter_kernel (char const*) ; 
 scalar_t__ strcmp (char const* const,char const*) ; 

__attribute__((used)) static const char *handle_scaler_opt(const char *name, bool tscale)
{
    if (name && name[0]) {
        const struct filter_kernel *kernel = mp_find_filter_kernel(name);
        if (kernel && (!tscale || !kernel->polar))
                return kernel->f.name;

        for (const char *const *filter = tscale ? fixed_tscale_filters
                                                : fixed_scale_filters;
             *filter; filter++) {
            if (strcmp(*filter, name) == 0)
                return *filter;
        }
    }
    return NULL;
}