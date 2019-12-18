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
struct TYPE_3__ {int max; void* min; } ;
typedef  TYPE_1__ zend_ssa_range ;
typedef  scalar_t__ zend_long ;

/* Variables and functions */
 void* MIN (scalar_t__,scalar_t__) ; 
 void* maxOR (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 void* minOR (scalar_t__,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void zend_ssa_range_or(zend_long a, zend_long b, zend_long c, zend_long d, zend_ssa_range *tmp)
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
			tmp->min = minOR(a, b, c, d);
			tmp->max = maxOR(a, b, c, d);
			break;
		case 0x2:
			tmp->min = minOR(a, b, c, -1);
			tmp->max = maxOR(a, b, 0, d);
			break;
		case 0x8:
			tmp->min = minOR(a, -1, c, d);
			tmp->max = maxOR(0, b, c, d);
			break;
		case 0xa:
			tmp->min = MIN(a, c);
			tmp->max = maxOR(0, b, 0, d);
			break;
		case 0xb:
			tmp->min = c;
			tmp->max = -1;
			break;
		case 0xe:
			tmp->min = a;
			tmp->max = -1;
			break;
	}
}