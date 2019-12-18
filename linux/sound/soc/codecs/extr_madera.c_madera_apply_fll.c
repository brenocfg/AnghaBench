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
struct madera_fll {scalar_t__ fout; } ;

/* Variables and functions */
 int /*<<< orphan*/  madera_disable_fll (struct madera_fll*) ; 
 int madera_enable_fll (struct madera_fll*) ; 

__attribute__((used)) static int madera_apply_fll(struct madera_fll *fll)
{
	if (fll->fout) {
		return madera_enable_fll(fll);
	} else {
		madera_disable_fll(fll);
		return 0;
	}
}