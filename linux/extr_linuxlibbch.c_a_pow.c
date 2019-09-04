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
struct bch_control {unsigned int* a_pow_tab; } ;

/* Variables and functions */
 size_t modulo (struct bch_control*,int) ; 

__attribute__((used)) static inline unsigned int a_pow(struct bch_control *bch, int i)
{
	return bch->a_pow_tab[modulo(bch, i)];
}