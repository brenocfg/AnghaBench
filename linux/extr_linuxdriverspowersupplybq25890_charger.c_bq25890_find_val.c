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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct bq25890_range {size_t step; scalar_t__ min; } ;
typedef  enum bq25890_table_ids { ____Placeholder_bq25890_table_ids } bq25890_table_ids ;
struct TYPE_3__ {scalar_t__* tbl; } ;
struct TYPE_4__ {struct bq25890_range rt; TYPE_1__ lt; } ;

/* Variables and functions */
 int TBL_TREG ; 
 TYPE_2__* bq25890_tables ; 

__attribute__((used)) static u32 bq25890_find_val(u8 idx, enum bq25890_table_ids id)
{
	const struct bq25890_range *rtbl;

	/* lookup table? */
	if (id >= TBL_TREG)
		return bq25890_tables[id].lt.tbl[idx];

	/* range table */
	rtbl = &bq25890_tables[id].rt;

	return (rtbl->min + idx * rtbl->step);
}