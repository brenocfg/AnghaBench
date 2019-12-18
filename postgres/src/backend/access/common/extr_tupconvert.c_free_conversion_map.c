#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* outisnull; struct TYPE_4__* outvalues; struct TYPE_4__* inisnull; struct TYPE_4__* invalues; struct TYPE_4__* attrMap; } ;
typedef  TYPE_1__ TupleConversionMap ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
free_conversion_map(TupleConversionMap *map)
{
	/* indesc and outdesc are not ours to free */
	pfree(map->attrMap);
	pfree(map->invalues);
	pfree(map->inisnull);
	pfree(map->outvalues);
	pfree(map->outisnull);
	pfree(map);
}