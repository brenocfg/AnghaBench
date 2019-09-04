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
typedef  size_t ut32 ;
struct TYPE_3__ {size_t symbols_by_ord_size; int /*<<< orphan*/ ** symbols_by_ord; } ;
typedef  int /*<<< orphan*/  RBinSymbol ;
typedef  TYPE_1__ ELFOBJ ;

/* Variables and functions */
 int /*<<< orphan*/  r_bin_symbol_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setsymord(ELFOBJ* eobj, ut32 ord, RBinSymbol *ptr) {
	if (!eobj->symbols_by_ord || ord >= eobj->symbols_by_ord_size) {
		return;
	}
	r_bin_symbol_free (eobj->symbols_by_ord[ord]);
	eobj->symbols_by_ord[ord] = ptr;
}