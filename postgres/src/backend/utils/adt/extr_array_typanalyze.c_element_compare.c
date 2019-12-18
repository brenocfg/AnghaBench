#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  coll_id; int /*<<< orphan*/  cmp; } ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* array_extra_data ; 

__attribute__((used)) static int
element_compare(const void *key1, const void *key2)
{
	Datum		d1 = *((const Datum *) key1);
	Datum		d2 = *((const Datum *) key2);
	Datum		c;

	c = FunctionCall2Coll(array_extra_data->cmp,
						  array_extra_data->coll_id,
						  d1, d2);
	return DatumGetInt32(c);
}