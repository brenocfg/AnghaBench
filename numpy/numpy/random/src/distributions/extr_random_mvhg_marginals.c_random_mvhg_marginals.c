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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  bitgen_t ;

/* Variables and functions */
 int random_hypergeometric (int /*<<< orphan*/ *,int,int,int) ; 

void random_mvhg_marginals(bitgen_t *bitgen_state,
                           int64_t total,
                           size_t num_colors, int64_t *colors,
                           int64_t nsample,
                           size_t num_variates, int64_t *variates)
{
    bool more_than_half;

    if ((total == 0) || (nsample == 0) || (num_variates == 0)) {
        // Nothing to do.
        return;
    }

    more_than_half = nsample > (total / 2);
    if (more_than_half) {
        nsample = total - nsample;
    }

    for (size_t i = 0; i < num_variates * num_colors; i += num_colors) {
        int64_t num_to_sample = nsample;
        int64_t remaining = total;
        for (size_t j = 0; (num_to_sample > 0) && (j + 1 < num_colors); ++j) {
            int64_t r;
            remaining -= colors[j];
            r = random_hypergeometric(bitgen_state,
                                      colors[j], remaining, num_to_sample);
            variates[i + j] = r;
            num_to_sample -= r;
        }

        if (num_to_sample > 0) {
            variates[i + num_colors - 1] = num_to_sample;
        }

        if (more_than_half) {
            for (size_t k = 0; k < num_colors; ++k) {
                variates[i + k] = colors[k] - variates[i + k];
            }
        }
    }
}