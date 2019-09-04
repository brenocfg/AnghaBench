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
struct bch_control {int* a_log_tab; } ;

/* Variables and functions */

__attribute__((used)) static inline int a_log(struct bch_control *bch, unsigned int x)
{
	return bch->a_log_tab[x];
}