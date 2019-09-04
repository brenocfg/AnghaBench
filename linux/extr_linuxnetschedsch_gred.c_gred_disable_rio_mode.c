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
struct gred_sched {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRED_RIO_MODE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gred_disable_rio_mode(struct gred_sched *table)
{
	__clear_bit(GRED_RIO_MODE, &table->flags);
}