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
typedef  int /*<<< orphan*/  u32 ;
struct pmagbbfb_par {scalar_t__ sfb; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void sfb_write(struct pmagbbfb_par *par, unsigned int reg, u32 v)
{
	writel(v, par->sfb + reg / 4);
}