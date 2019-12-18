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
 scalar_t__ random_interval (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int64_t hypergeometric_sample(bitgen_t *bitgen_state,
                                     int64_t good, int64_t bad, int64_t sample)
{
    int64_t remaining_total, remaining_good, result, computed_sample;
    int64_t total = good + bad;

    if (sample > total/2) {
        computed_sample = total - sample;
    }
    else {
        computed_sample = sample;
    }

    remaining_total = total;
    remaining_good = good;

    while ((computed_sample > 0) && (remaining_good > 0) &&
           (remaining_total > remaining_good)) {
         // random_interval(bitgen_state, max) returns an integer in
         // [0, max] *inclusive*, so we decrement remaining_total before
         // passing it to random_interval().
        --remaining_total;
        if ((int64_t) random_interval(bitgen_state,
                                      remaining_total) < remaining_good) {
            // Selected a "good" one, so decrement remaining_good.
            --remaining_good;
        }
        --computed_sample;
    }

    if (remaining_total == remaining_good) {
        // Only "good" choices are left.
        remaining_good -= computed_sample;
    }

    if (sample > total/2) {
        result = remaining_good;
    }
    else {
        result = good - remaining_good;
    }

    return result;
}