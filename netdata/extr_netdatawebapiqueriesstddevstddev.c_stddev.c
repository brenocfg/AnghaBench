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
struct grouping_stddev {int dummy; } ;
typedef  int /*<<< orphan*/  calculated_number ;

/* Variables and functions */
 int /*<<< orphan*/  sqrtl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  variance (struct grouping_stddev*) ; 

__attribute__((used)) static inline calculated_number stddev(struct grouping_stddev *g) {
    return sqrtl(variance(g));
}