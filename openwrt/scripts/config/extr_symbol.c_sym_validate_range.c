#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  val; } ;
struct symbol {int type; TYPE_4__ curr; } ;
struct property {TYPE_3__* expr; } ;
struct TYPE_6__ {int /*<<< orphan*/  sym; } ;
struct TYPE_5__ {int /*<<< orphan*/  sym; } ;
struct TYPE_7__ {TYPE_2__ right; TYPE_1__ left; } ;

/* Variables and functions */
#define  S_HEX 129 
#define  S_INT 128 
 int /*<<< orphan*/  sprintf (char*,char*,long long) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 long long strtoll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct property* sym_get_range_prop (struct symbol*) ; 
 long long sym_get_range_val (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sym_validate_range(struct symbol *sym)
{
	struct property *prop;
	int base;
	long long val, val2;
	char str[64];

	switch (sym->type) {
	case S_INT:
		base = 10;
		break;
	case S_HEX:
		base = 16;
		break;
	default:
		return;
	}
	prop = sym_get_range_prop(sym);
	if (!prop)
		return;
	val = strtoll(sym->curr.val, NULL, base);
	val2 = sym_get_range_val(prop->expr->left.sym, base);
	if (val >= val2) {
		val2 = sym_get_range_val(prop->expr->right.sym, base);
		if (val <= val2)
			return;
	}
	if (sym->type == S_INT)
		sprintf(str, "%lld", val2);
	else
		sprintf(str, "0x%llx", val2);
	sym->curr.val = strdup(str);
}