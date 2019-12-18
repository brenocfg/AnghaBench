#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* gen; } ;
typedef  TYPE_2__ relopt_value ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 scalar_t__ GET_STRING_RELOPTION_LEN (TYPE_2__) ; 
 scalar_t__ RELOPT_TYPE_STRING ; 
 void* palloc0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
allocateReloptStruct(Size base, relopt_value *options, int numoptions)
{
	Size		size = base;
	int			i;

	for (i = 0; i < numoptions; i++)
		if (options[i].gen->type == RELOPT_TYPE_STRING)
			size += GET_STRING_RELOPTION_LEN(options[i]) + 1;

	return palloc0(size);
}