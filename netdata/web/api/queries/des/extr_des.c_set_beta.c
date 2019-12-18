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
struct grouping_des {double beta; double beta_other; } ;
typedef  int /*<<< orphan*/  RRDR ;

/* Variables and functions */
 double window (int /*<<< orphan*/ *,struct grouping_des*) ; 

__attribute__((used)) static inline void set_beta(RRDR *r, struct grouping_des *g) {
    // https://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average
    // A commonly used value for alpha is 2 / (N + 1)

    g->beta = 2.0 / (window(r, g) + 1.0);
    g->beta_other = 1.0 - g->beta;

    //info("beta for chart '%s' is " CALCULATED_NUMBER_FORMAT, r->st->name, g->beta);
}