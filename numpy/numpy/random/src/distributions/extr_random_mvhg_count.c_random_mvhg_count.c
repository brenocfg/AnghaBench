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
 int /*<<< orphan*/  free (size_t*) ; 
 size_t* malloc (int) ; 
 scalar_t__ random_interval (int /*<<< orphan*/ *,size_t) ; 

int random_mvhg_count(bitgen_t *bitgen_state,
                      int64_t total,
                      size_t num_colors, int64_t *colors,
                      int64_t nsample,
                      size_t num_variates, int64_t *variates)
{
    size_t *choices;
    bool more_than_half;

    if ((total == 0) || (nsample == 0) || (num_variates == 0)) {
        // Nothing to do.
        return 0;
    }

    choices = malloc(total * (sizeof *choices));
    if (choices == NULL) {
        return -1;
    }

    /*
     *  If colors contains, for example, [3 2 5], then choices
     *  will contain [0 0 0 1 1 2 2 2 2 2].
     */
    for (size_t i = 0, k = 0; i < num_colors; ++i) {
        for (int64_t j = 0; j < colors[i]; ++j) {
            choices[k] = i;
            ++k;
        }
    }

    more_than_half = nsample > (total / 2);
    if (more_than_half) {
        nsample = total - nsample;
    }

    for (size_t i = 0; i < num_variates * num_colors; i += num_colors) {
        /*
         *  Fisher-Yates shuffle, but only loop through the first
         *  `nsample` entries of `choices`.  After the loop,
         *  choices[:nsample] contains a random sample from the
         *  the full array.
         */
        for (size_t j = 0; j < (size_t) nsample; ++j) {
            size_t tmp, k;
            // Note: nsample is not greater than total, so there is no danger
            // of integer underflow in `(size_t) total - j - 1`.
            k = j + (size_t) random_interval(bitgen_state,
                                             (size_t) total - j - 1);
            tmp = choices[k];
            choices[k] = choices[j];
            choices[j] = tmp;
        }
        /*
         *  Count the number of occurrences of each value in choices[:nsample].
         *  The result, stored in sample[i:i+num_colors], is the sample from
         *  the multivariate hypergeometric distribution.
         */
        for (size_t j = 0; j < (size_t) nsample; ++j) {
            variates[i + choices[j]] += 1;
        }

        if (more_than_half) {
            for (size_t k = 0; k < num_colors; ++k) {
                variates[i + k] = colors[k] - variates[i + k];
            }
        }
    }

    free(choices);

    return 0;
}