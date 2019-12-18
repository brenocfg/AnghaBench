#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct madera_fll {int /*<<< orphan*/  fout; TYPE_1__* madera; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  rev; } ;

/* Variables and functions */
#define  CS47L35 130 
#define  CS47L85 129 
#define  WM1840 128 
 int madera_find_main_fratio (unsigned int,int /*<<< orphan*/ ,int*) ; 
 int madera_find_sync_fratio (unsigned int,int*) ; 

__attribute__((used)) static int madera_find_fratio(struct madera_fll *fll, unsigned int fref,
			      bool sync, int *fratio)
{
	switch (fll->madera->type) {
	case CS47L35:
		switch (fll->madera->rev) {
		case 0:
			/* rev A0 uses sync calculation for both loops */
			return madera_find_sync_fratio(fref, fratio);
		default:
			if (sync)
				return madera_find_sync_fratio(fref, fratio);
			else
				return madera_find_main_fratio(fref,
							       fll->fout,
							       fratio);
		}
		break;
	case CS47L85:
	case WM1840:
		/* these use the same calculation for main and sync loops */
		return madera_find_sync_fratio(fref, fratio);
	default:
		if (sync)
			return madera_find_sync_fratio(fref, fratio);
		else
			return madera_find_main_fratio(fref, fll->fout, fratio);
	}
}