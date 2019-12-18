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
struct TYPE_3__ {scalar_t__ name; } ;
typedef  TYPE_1__ RBinSymbol ;

/* Variables and functions */
 int /*<<< orphan*/  strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static inline bool check_objc(RBinSymbol *sym) {
	if (sym->name && !strncmp (sym->name, "_OBJC_", 6)) {
		// free (r_bin_demangle_objc (binfile, sym->name));
		return true;
	}
	return false;
}