#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct block_range {scalar_t__ coverage; struct symbol* sym; } ;
struct TYPE_4__ {scalar_t__ blocks; } ;
struct TYPE_3__ {double max_coverage; } ;

/* Variables and functions */
 TYPE_2__ block_ranges ; 
 TYPE_1__* symbol__annotation (struct symbol*) ; 

double block_range__coverage(struct block_range *br)
{
	struct symbol *sym;

	if (!br) {
		if (block_ranges.blocks)
			return 0;

		return -1;
	}

	sym = br->sym;
	if (!sym)
		return -1;

	return (double)br->coverage / symbol__annotation(sym)->max_coverage;
}