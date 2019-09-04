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
struct intc_desc_int {int dummy; } ;
struct intc_desc {int dummy; } ;
typedef  int /*<<< orphan*/  intc_enum ;

/* Variables and functions */

__attribute__((used)) static inline void
intc_set_dist_handle(unsigned int irq, struct intc_desc *desc,
		     struct intc_desc_int *d, intc_enum id) { }