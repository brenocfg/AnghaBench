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
struct bch_control {unsigned int* a_pow_tab; size_t* a_log_tab; } ;

/* Variables and functions */
 size_t GF_N (struct bch_control*) ; 

__attribute__((used)) static inline unsigned int gf_inv(struct bch_control *bch, unsigned int a)
{
	return bch->a_pow_tab[GF_N(bch)-bch->a_log_tab[a]];
}