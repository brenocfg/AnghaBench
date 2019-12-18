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
struct TYPE_3__ {int /*<<< orphan*/  symbol; } ;
typedef  TYPE_1__ RBinReloc ;

/* Variables and functions */
 int is_section_symbol (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_section_reloc(RBinReloc *r) {
	return is_section_symbol (r->symbol);
}