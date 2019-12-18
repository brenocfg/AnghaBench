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
struct error_diffusion_kernel {int dummy; } ;

/* Variables and functions */
 int EF_MAX_DELTA_Y ; 
 int compute_rightmost_shifted_column (struct error_diffusion_kernel const*) ; 

int mp_ef_compute_shared_memory_size(const struct error_diffusion_kernel *k,
                                     int height)
{
    // We add EF_MAX_DELTA_Y empty lines on the bottom to handle errors
    // propagated out from bottom side.
    int rows = height + EF_MAX_DELTA_Y;
    int shifted_columns = compute_rightmost_shifted_column(k) + 1;

    // The shared memory is an array of size rows*shifted_columns. Each element
    // is a single uint for three RGB component.
    return rows * shifted_columns * 4;
}