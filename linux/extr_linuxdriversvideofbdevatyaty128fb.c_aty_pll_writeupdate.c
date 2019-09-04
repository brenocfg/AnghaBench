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
struct aty128fb_par {int dummy; } ;

/* Variables and functions */
 int PPLL_ATOMIC_UPDATE_W ; 
 int /*<<< orphan*/  PPLL_REF_DIV ; 
 int aty_ld_pll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aty_pll_wait_readupdate (struct aty128fb_par const*) ; 
 int /*<<< orphan*/  aty_st_pll (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aty_pll_writeupdate(const struct aty128fb_par *par)
{
	aty_pll_wait_readupdate(par);

	aty_st_pll(PPLL_REF_DIV,
		   aty_ld_pll(PPLL_REF_DIV) | PPLL_ATOMIC_UPDATE_W);
}