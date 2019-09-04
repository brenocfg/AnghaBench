#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct tnum {scalar_t__ mask; scalar_t__ value; } ;
typedef  int s64 ;

/* Variables and functions */
 struct tnum TNUM (int,int) ; 

struct tnum tnum_arshift(struct tnum a, u8 min_shift)
{
	/* if a.value is negative, arithmetic shifting by minimum shift
	 * will have larger negative offset compared to more shifting.
	 * If a.value is nonnegative, arithmetic shifting by minimum shift
	 * will have larger positive offset compare to more shifting.
	 */
	return TNUM((s64)a.value >> min_shift, (s64)a.mask >> min_shift);
}