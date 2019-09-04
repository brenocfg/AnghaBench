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
struct TYPE_3__ {void* max; void* min; } ;
typedef  TYPE_1__ zend_ssa_range ;
typedef  scalar_t__ zend_long ;

/* Variables and functions */
 void* MAX (scalar_t__,scalar_t__) ; 
 void* maxAND (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 void* minAND (scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void zend_ssa_range_and(zend_long a, zend_long b, zend_long c, zend_long d, zend_ssa_range *tmp)
{
	int x = ((a < 0) ? 8 : 0) |
	        ((b < 0) ? 4 : 0) |
	        ((c < 0) ? 2 : 0) |
	        ((d < 0) ? 2 : 0);
	switch (x) {
		case 0x0:
		case 0x3:
		case 0xc:
		case 0xf:
			tmp->min = minAND(a, b, c, d);
			tmp->max = maxAND(a, b, c, d);
			break;
		case 0x2:
			tmp->min = 0;
			tmp->max = b;
			break;
		case 0x8:
			tmp->min = 0;
			tmp->max = d;
			break;
		case 0xa:
			tmp->min = minAND(a, -1, c, -1);
			tmp->max = MAX(b, d);
			break;
		case 0xb:
			tmp->min = minAND(a, -1, c, d);
			tmp->max = maxAND(0, b, c, d);
			break;
		case 0xe:
			tmp->min = minAND(a, b, c, -1);
			tmp->max = maxAND(a, b, 0, d);
			break;
	}
}