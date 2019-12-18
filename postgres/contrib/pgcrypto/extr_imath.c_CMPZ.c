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
typedef  TYPE_1__* mp_int ;
struct TYPE_3__ {int used; scalar_t__* digits; scalar_t__ sign; } ;

/* Variables and functions */
 scalar_t__ MP_NEG ; 

__attribute__((used)) static inline int
CMPZ(mp_int Z)
{
	if (Z->used == 1 && Z->digits[0] == 0)
		return 0;
	return (Z->sign == MP_NEG) ? -1 : 1;
}