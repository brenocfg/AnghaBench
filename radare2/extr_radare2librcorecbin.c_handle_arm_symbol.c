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
struct TYPE_3__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  paddr; } ;
typedef  int /*<<< orphan*/  RCore ;
typedef  TYPE_1__ RBinSymbol ;
typedef  int /*<<< orphan*/  RBinInfo ;

/* Variables and functions */
 void handle_arm_hint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handle_arm_symbol(RCore *core, RBinSymbol *symbol, RBinInfo *info, int va) {
	return handle_arm_hint (core, info, symbol->paddr, symbol->vaddr, symbol->bits, va);
}