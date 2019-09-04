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
typedef  int u32 ;
struct TYPE_3__ {int ioasc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int IPR_IOASC_IOASC_MASK ; 
 TYPE_1__* ipr_error_table ; 

__attribute__((used)) static u32 ipr_get_error(u32 ioasc)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ipr_error_table); i++)
		if (ipr_error_table[i].ioasc == (ioasc & IPR_IOASC_IOASC_MASK))
			return i;

	return 0;
}