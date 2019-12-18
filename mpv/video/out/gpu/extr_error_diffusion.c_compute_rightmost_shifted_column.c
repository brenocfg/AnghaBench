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
struct error_diffusion_kernel {scalar_t__** pattern; int shift; } ;

/* Variables and functions */
 int EF_MAX_DELTA_X ; 
 int EF_MAX_DELTA_Y ; 
 int EF_MIN_DELTA_X ; 
 int MPMAX (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int compute_rightmost_shifted_column(const struct error_diffusion_kernel *k)
{
    int ret = 0;
    for (int y = 0; y <= EF_MAX_DELTA_Y; y++) {
        for (int x = EF_MIN_DELTA_X; x <= EF_MAX_DELTA_X; x++) {
            if (k->pattern[y][x - EF_MIN_DELTA_X] != 0) {
                int shifted_x = x + y * k->shift;

                // The shift mapping guarantees current column (or left of it)
                // won't be affected by error diffusion.
                assert(shifted_x > 0);

                ret = MPMAX(ret, shifted_x);
            }
        }
    }
    return ret;
}