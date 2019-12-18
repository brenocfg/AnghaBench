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
struct error_diffusion_kernel {scalar_t__ name; } ;

/* Variables and functions */
 struct error_diffusion_kernel* mp_error_diffusion_kernels ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

const struct error_diffusion_kernel *mp_find_error_diffusion_kernel(const char *name)
{
    if (!name)
        return NULL;
    for (const struct error_diffusion_kernel *k = mp_error_diffusion_kernels;
         k->name;
         k++) {
        if (strcmp(k->name, name) == 0)
            return k;
    }
    return NULL;
}