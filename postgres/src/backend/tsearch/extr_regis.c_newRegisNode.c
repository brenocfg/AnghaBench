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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ RegisNode ;

/* Variables and functions */
 scalar_t__ RNHDRSZ ; 
 scalar_t__ palloc0 (scalar_t__) ; 

__attribute__((used)) static RegisNode *
newRegisNode(RegisNode *prev, int len)
{
	RegisNode  *ptr;

	ptr = (RegisNode *) palloc0(RNHDRSZ + len + 1);
	if (prev)
		prev->next = ptr;
	return ptr;
}