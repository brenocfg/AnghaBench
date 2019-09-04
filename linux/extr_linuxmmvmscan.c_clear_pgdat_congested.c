#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  PGDAT_CONGESTED ; 
 int /*<<< orphan*/  PGDAT_DIRTY ; 
 int /*<<< orphan*/  PGDAT_WRITEBACK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_pgdat_congested(pg_data_t *pgdat)
{
	clear_bit(PGDAT_CONGESTED, &pgdat->flags);
	clear_bit(PGDAT_DIRTY, &pgdat->flags);
	clear_bit(PGDAT_WRITEBACK, &pgdat->flags);
}