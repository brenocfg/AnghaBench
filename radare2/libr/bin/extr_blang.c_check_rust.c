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
 scalar_t__ strstr (scalar_t__,char*) ; 

__attribute__((used)) static inline bool check_rust(RBinSymbol *sym) {
	return sym->name && strstr (sym->name, "_$LT$");
}