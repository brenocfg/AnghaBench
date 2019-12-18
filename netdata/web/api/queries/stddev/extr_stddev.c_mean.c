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
struct grouping_stddev {scalar_t__ count; double m_newM; } ;
typedef  double calculated_number ;

/* Variables and functions */

__attribute__((used)) static inline calculated_number mean(struct grouping_stddev *g) {
    return (g->count > 0) ? g->m_newM : 0.0;
}