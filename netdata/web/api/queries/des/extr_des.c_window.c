#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct grouping_des {int dummy; } ;
typedef  int calculated_number ;
struct TYPE_4__ {int points_wanted; } ;
struct TYPE_5__ {int group; TYPE_1__ internal; } ;
typedef  TYPE_2__ RRDR ;

/* Variables and functions */
 int max_window_size ; 

__attribute__((used)) static inline calculated_number window(RRDR *r, struct grouping_des *g) {
    (void)g;

    calculated_number points;
    if(r->group == 1) {
        // provide a running DES
        points = r->internal.points_wanted;
    }
    else {
        // provide a SES with flush points
        points = r->group;
    }

    // https://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average
    // A commonly used value for alpha is 2 / (N + 1)
    return (points > max_window_size) ? max_window_size : points;
}